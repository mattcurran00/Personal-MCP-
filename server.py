from fastmcp import FastMCP

mcp = FastMCP("Test Server")

@mcp.tool
def add(a: int, b: int) -> int:
    return a + b

if __name__ == "__main__":
    print("Starting Server...")
    mcp.run()