import os 
from anthropic import Anthropic
import asyncio
from fastmcp import Client

anthropic = Anthropic(api_key=os.environ.get("ANTHROPIC_API_KEY"))

async def callmodel(message: list) -> str:
    async with Client("server.py") as mcpClient:

        mcp_tools = await mcpClient.list_tools()

        tools = [
            {
                "name": t.name,
                "description": t.description or "",
                # MCP uses camelCase (inputSchema), Anthropic uses snake_case (input_schema)
                "input_schema": t.inputSchema,
            }
            for t in mcp_tools
        ]

        # Copy so intermediate tool turns don't pollute the caller's history
        workingMessages = message.copy()

        while True:
            # max_tokens is required by the API
            response = anthropic.messages.create(
                model="claude-haiku-4-5-20251001",
                max_tokens=1024,
                tools=tools,
                messages=workingMessages,
            )

            # Claude finished — return its text reply
            if response.stop_reason == "end_turn":
                return next(b.text for b in response.content if b.type == "text")

            # Claude wants to call a tool before answering
            if response.stop_reason == "tool_use":

                # The API requires Claude's response (with tool_use blocks) to be
                # recorded as an assistant turn before we add results
                workingMessages.append({
                    "role": "assistant",
                    "content": response.content,
                })

                # Run each tool call and collect results
                tool_results = []
                for block in response.content:
                    if block.type == "tool_use":
                        # block.name = tool to call, block.input = its arguments
                        # block.id links this result back to the request
                        result = await mcpClient.call_tool(block.name, block.input)
                        content = result[0].text if result else "no result"
                        tool_results.append({
                            "type": "tool_result",
                            "tool_use_id": block.id,
                            "content": content,
                        })

                # Feed results back to Claude as a user turn, then loop again
                workingMessages.append({
                    "role": "user",
                    "content": tool_results,
                })

