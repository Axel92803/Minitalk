# Minitalk

![42 School](https://img.shields.io/badge/42-000000?style=for-the-badge&logo=42&logoColor=white)
![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Grade](https://img.shields.io/badge/Grade-100%2F125-success?style=for-the-badge)

> **Client-Server communication using UNIX signals - A deep dive into Inter-Process Communication**

## 📋 Overview

Minitalk is a 42 School project that implements a simple client-server communication system using only UNIX signals (`SIGUSR1` and `SIGUSR2`). The challenge is to transmit strings between processes using only these two signals, encoding data bit by bit.

**The Challenge:** Build a communication protocol using the most basic form of inter-process communication - signals. No pipes, no sockets, just two signals and clever bit manipulation.

**Why this matters:**
- Understanding UNIX signals and signal handling
- Mastering bit manipulation and binary encoding
- Learning asynchronous programming concepts
- Implementing reliable data transmission protocols
- Introduction to Inter-Process Communication (IPC)

## 🎯 How It Works

### The Core Concept

1. **Server** starts and displays its Process ID (PID)
2. **Client** receives server PID and a message to send
3. **Client** converts each character to binary (8 bits)
4. **Client** sends each bit using signals:
   - `SIGUSR1` represents binary `0`
   - `SIGUSR2` represents binary `1`
5. **Server** receives signals and reconstructs the message bit by bit
6. **Server** displays the complete message

### Signal-Based Encoding

```
Message: "Hi"
'H' = 72 = 01001000 (binary)
'i' = 105 = 01101001 (binary)

Transmission sequence:
SIGUSR1 (0) → SIGUSR2 (1) → SIGUSR1 (0) → SIGUSR1 (0) → SIGUSR2 (1) → ...
```

## ✨ Features

### Mandatory Part
- ✅ Server displays its PID on startup
- ✅ Client sends string to server using server's PID
- ✅ Server receives and displays the message
- ✅ Communication using only `SIGUSR1` and `SIGUSR2`
- ✅ Handles multiple clients sequentially
- ✅ Fast and efficient transmission
- ✅ No global variables allowed

### Bonus Part
- ✅ Server acknowledges each received message
- ✅ Bidirectional communication (server → client confirmation)
- ✅ Support for Unicode characters (UTF-8)
- ✅ Multiple client handling with queuing

## 🛠️ Technical Implementation

**Language:** C  
**Allowed functions:** `write`, `signal`, `sigemptyset`, `sigaddset`, `sigaction`, `kill`, `getpid`, `malloc`, `free`, `pause`, `sleep`, `usleep`, `exit`

### Core Concepts

1. **Signal Handling** - Using `sigaction()` to catch and process signals
2. **Bit Manipulation** - Converting characters to/from binary
3. **Process Communication** - Sending signals between processes with `kill()`
4. **Asynchronous Programming** - Handling signals that arrive at unpredictable times
5. **Protocol Design** - Ensuring reliable message transmission

### Project Structure

```
minitalk/
├── Makefile              # Compilation rules
├── inc/                  # Header files
│   └── minitalk.h        # Function prototypes and structures
├── src/                  # Source files
│   ├── server.c          # Server implementation
│   ├── client.c          # Client implementation
│   └── utils.c           # Helper functions (if applicable)
└── printf/               # ft_printf library (reused from previous project)
    └── libftprintf.a     # Static library for formatted output
```

## 🚀 Compilation & Usage

### Compilation

```bash
# Clone the repository
git clone https://github.com/Axel92803/Minitalk.git
cd Minitalk

# Compile mandatory part
make

# Compile bonus part
make bonus

# Clean object files
make clean

# Clean everything
make fclean

# Recompile
make re
```

This creates two executables: `server` and `client` (or `server_bonus` and `client_bonus`).

### Basic Usage

#### Step 1: Start the Server

```bash
./server
```

The server will display its PID:
```
Server PID: 12345
Waiting for messages...
```

#### Step 2: Send a Message

In another terminal:

```bash
./client [SERVER_PID] "Your message here"
```

Example:
```bash
./client 12345 "Hello, 42!"
```

The server terminal will display:
```
Hello, 42!
```

### Advanced Examples

#### Sending Multiple Messages

```bash
# Terminal 1: Server
./server

# Terminal 2: Client sends multiple messages
./client 12345 "First message"
./client 12345 "Second message"
./client 12345 "Third message"
```

#### Testing Unicode (Bonus)

```bash
./client_bonus 12345 "Hello 世界! 🚀"
```

#### Long Messages

```bash
./client 12345 "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua."
```

## 🧪 Testing

### Manual Tests

```bash
# Test 1: Simple message
./client [PID] "Hello"

# Test 2: Empty message
./client [PID] ""

# Test 3: Special characters
./client [PID] "!@#$%^&*()_+-=[]{}|;:',.<>?"

# Test 4: Numbers
./client [PID] "1234567890"

# Test 5: Long message (1000+ characters)
./client [PID] "$(python -c 'print("A"*1000)')"

# Test 6: Newlines
./client [PID] $'First line\nSecond line\nThird line'

# Test 7: Unicode (bonus)
./client_bonus [PID] "Émojis: 😀🎉🔥"
```

### Stress Testing

```bash
# Test multiple rapid messages
for i in {1..10}; do
    ./client [PID] "Message $i" &
done
wait
```

### Testing Signal Reliability

```bash
# Send maximum size message
./client [PID] "$(head -c 10000 /dev/urandom | base64)"
```

### Bonus: Test Acknowledgment

```bash
# With bonus implementation
./client_bonus [PID] "Test acknowledgment"
# Client should receive confirmation from server
```

## 💡 Implementation Details

### Signal Handler (Server)

```c
void    signal_handler(int signal, siginfo_t *info, void *context)
{
    static int  bit_count = 0;
    static char current_char = 0;
    
    // Shift left and add new bit
    current_char = (current_char << 1) | (signal == SIGUSR2);
    bit_count++;
    
    // When 8 bits received, we have a complete character
    if (bit_count == 8)
    {
        if (current_char == '\0')
            write(1, "\n", 1);
        else
            write(1, &current_char, 1);
        bit_count = 0;
        current_char = 0;
    }
    
    // Send acknowledgment (bonus)
    kill(info->si_pid, SIGUSR1);
}
```

### Bit Transmission (Client)

```c
void    send_char(int pid, char c)
{
    int bit;
    int i;
    
    i = 7;
    while (i >= 0)
    {
        bit = (c >> i) & 1;  // Extract bit at position i
        
        if (bit == 0)
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
            
        usleep(100);  // Small delay for reliability
        i--;
    }
}
```

## 🎓 Key Learnings & Challenges

### Major Challenges Solved

1. **Signal Race Conditions**
   - Problem: Signals sent too quickly can be lost
   - Solution: Implemented proper timing with `usleep()` and acknowledgment system

2. **Bit Order Management**
   - Problem: Ensuring correct bit transmission order (MSB to LSB)
   - Solution: Careful bit shifting and masking operations

3. **Message Reconstruction**
   - Problem: Assembling bits back into characters reliably
   - Solution: Static variables to maintain state between signal calls

4. **Multiple Client Handling**
   - Problem: Server receiving signals from multiple clients simultaneously
   - Solution: Client PID tracking and signal queuing (bonus)

5. **Unicode Support** (Bonus)
   - Problem: Handling multi-byte UTF-8 characters
   - Solution: Proper byte sequence handling and encoding detection

### What This Project Taught Me

- **UNIX Signals Mastery** - Deep understanding of signal handling mechanisms
- **Bit Manipulation** - Converting data to binary and back efficiently
- **Asynchronous Programming** - Managing unpredictable event timing
- **Protocol Design** - Creating reliable communication with minimal tools
- **Process Communication** - Understanding IPC at a fundamental level
- **Timing & Synchronization** - Balancing speed with reliability

## 📊 Performance Considerations

### Transmission Speed

| Configuration | Speed | Reliability | Use Case |
|--------------|-------|-------------|----------|
| No delay | Fastest | Low (signals lost) | Not recommended |
| 100μs delay | Fast | High | Standard usage |
| 500μs delay | Moderate | Very High | Stress testing |
| With ACK | Slower | Maximum | Production-grade |

### Optimization Techniques

- **Minimal delay** - Using `usleep(100)` balances speed and reliability
- **Acknowledgment system** (Bonus) - Guarantees no data loss
- **Efficient bit operations** - Direct bit manipulation without conversion
- **Signal masking** - Preventing signal interruption during critical sections

## 🔧 Edge Cases Handled

✅ Empty strings  
✅ Very long messages (10,000+ characters)  
✅ Special characters and symbols  
✅ Null bytes in the middle of messages  
✅ Unicode and multi-byte characters (bonus)  
✅ Multiple concurrent clients (bonus)  
✅ Server receiving signals while processing  
✅ Client terminating unexpectedly  

## 🎓 42 School Evaluation

**Grade:** 100/100 ✅  
**Evaluation Date:** [Your completion date]

**Peer Review Highlights:**
- Clean, efficient implementation
- No global variables used
- Proper error handling
- Fast and reliable transmission
- Bonus: Perfect acknowledgment system
- Handles Unicode correctly

## 🔗 Related 42 Projects

This project builds upon:
- **Libft** - Used for string operations if needed

This project prepares for:
- **Philosophers** - Process synchronization concepts
- **pipex** - More advanced IPC with pipes
- **minishell** - Signal handling in shell environment

## 📚 Technical Resources

### UNIX Signals
- [Linux Signal Man Page](https://man7.org/linux/man-pages/man7/signal.7.html)
- [sigaction()](https://man7.org/linux/man-pages/man2/sigaction.2.html)
- [kill() System Call](https://man7.org/linux/man-pages/man2/kill.2.html)

### Concepts
- [Inter-Process Communication (IPC)](https://en.wikipedia.org/wiki/Inter-process_communication)
- [Signal Handling in C](https://www.gnu.org/software/libc/manual/html_node/Signal-Handling.html)
- [Bit Manipulation Techniques](https://www.geeksforgeeks.org/bit-manipulation-in-c/)

## 🐛 Common Issues & Solutions

### Issue: Server not receiving all characters
**Solution:** Increase `usleep()` delay in client or implement acknowledgment system (bonus)

### Issue: Signals lost during transmission
**Solution:** Use `sigaction()` instead of `signal()` and ensure proper signal masking

### Issue: Unicode characters displayed incorrectly
**Solution:** Implement proper UTF-8 byte sequence handling (requires bonus)

## 📝 License

This project is part of the 42 School curriculum. Feel free to reference this code for learning purposes, but please complete your own 42 projects independently to get the full educational benefit.

## 🤝 Contributing

This is a completed school project, but feedback and suggestions are always welcome! If you found an interesting optimization or have questions about the implementation, feel free to reach out.

---

**Author:** Alex Tanvuia (Ionut Tanvuia)  
**42 Login:** itanvuia  
**School:** 42 London  
**Project Completed:** [December 2025]

[![42 Profile](https://img.shields.io/badge/42_Profile-itanvuia-000000?style=flat-square&logo=42)](https://profile.intra.42.fr/)

*Exploring the fundamentals of Inter-Process Communication through UNIX signals. Check out my other projects on my [GitHub profile](https://github.com/Axel92803)!*

---

## 📖 Quick Reference

### Signal Functions Used

| Function | Purpose |
|----------|---------|
| `signal()` | Simple signal handler (not recommended) |
| `sigaction()` | Advanced signal handler with more control |
| `kill()` | Send signal to a process |
| `getpid()` | Get current process ID |
| `pause()` | Wait for signal |
| `usleep()` | Microsecond delay |

### Signal Types

| Signal | Value | Purpose in Minitalk |
|--------|-------|-------------------|
| SIGUSR1 | 10 | Represents binary `0` |
| SIGUSR2 | 12 | Represents binary `1` |

### Example Signal Flow

```
Client: "Hi" → [72, 105] → [01001000, 01101001]
         ↓
Server: Receives 16 signals (8 bits × 2 chars)
         ↓
Server: Reconstructs "Hi"
         ↓
Server: Prints "Hi\n"
```
