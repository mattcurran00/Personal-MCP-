import os 
from anthropic import Anthropic
import asyncio
from fastmcp import Client
from clichat import CLIChat

client = Anthropic(api_key=os.environ.get("ANTHROPIC_API_KEY"))

print(f"Key is: {client}") #testing if its accessible 

async def main():
    async with Client("server.py") as mcpClient:
        mcp_tools = await mcpClient.list_tools()


        anthropic_tools = [
            {
                "name": t.name,
                "description": t.description,
                "input_schema": t.inputSchema,
            }
            for t in mcp_tools
        ]

    async def passmessage(message: str) -> None:
        

