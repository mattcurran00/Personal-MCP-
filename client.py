import asyncio

from fastmcp import Client

async def main() -> None:
    client = Client("server.py")

    async with client:
        tools = await client.list_tools()

        print("Available Tools: ")
        for tool in tools:
            print(f" - {tool.name}")

        result = await client.call_tool(
            "add",
            {
                "a": 10,
                "b": 5,
            },
        )

        print("Result: ", result)

if __name__ == "__main__":
    asyncio.run(main())