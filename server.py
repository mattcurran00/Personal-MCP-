from fastmcp import FastMCP
import subprocess

mcp = FastMCP("Test Server")

@mcp.tool
def add(a: int, b: int) -> int:
    return a + b

#try to make a tool that reads a file and prints it
@mcp.tool
def readFile(fname: str) -> None:
    try:
        command = "./c/test" + " " + fname
        subprocess.run([command])
    except:
        print("Goosed")

if __name__ == "__main__":
    print("Starting Server...")
    mcp.run()