# 💬 ft_irc – IRC Server

> A multi-client IRC server built in C++98 as part of the 42 Network curriculum.

---

## 📌 Project Overview

**ft_irc** is a real-time chat server that implements a simplified version of the [IRC (Internet Relay Chat)](https://tools.ietf.org/html/rfc1459) protocol. The server handles multiple clients simultaneously using sockets, allowing them to connect, join channels, and communicate using IRC commands.

This project was built using low-level socket programming, without relying on external libraries — strictly using **C++98** and the POSIX API.

---

## ⚙️ Features

- 🧠 Built from scratch in **C++98**
- 📡 Handles multiple clients using non-blocking sockets & `poll()`
- 🔐 User authentication with nickname & password
- 💬 IRC commands: `JOIN`, `PART`, `PRIVMSG`, `QUIT`, `TOPIC`, `KICK`, `MODE`, etc.
- 📁 Channel management with permissions and modes
- 🧵 Efficient event loop for real-time communication
- ❌ Graceful handling of disconnections and errors

---

## 🧱 Technologies

- **C++98**
- **POSIX sockets**
- **poll()** for multiplexing
- No external libraries


