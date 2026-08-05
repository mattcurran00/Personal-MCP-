import asyncio
from modelcall import call_model


class CLIChat:
    def __init__(self) -> None:
        self.running = True
        # Persistent message history for the whole session.
        # We keep appending to this so Claude remembers the conversation.
        self.history = []

    async def startChat(self) -> None:
        print("CLI Chat (MCP-powered)")
        print("/exit to quit")

        while self.running:
            try:
                message = input("You > ").strip()

                if not message:
                    continue

                await self.handle_message(message)

            except KeyboardInterrupt:
                print("\nUse /exit to quit.")

        print("Goodbye")

    async def handle_message(self, message: str) -> None:
        if message == "/exit":
            self.running = False
            return

        # Add the user's message to history before calling the model.
        # History is a list of {"role": ..., "content": ...} dicts —
        # exactly the format the Anthropic API expects.
        self.history.append({"role": "user", "content": message})

        # call_model sends the full history to Claude (with MCP tools available)
        # and returns Claude's final text reply.
        response = await call_model(self.history)

        # Record Claude's reply in history so the next turn has full context.
        self.history.append({"role": "assistant", "content": response})

        print(f"Claude > {response}")


async def main() -> None:
    chat = CLIChat()
    await chat.startChat()


if __name__ == "__main__":
    asyncio.run(main())
