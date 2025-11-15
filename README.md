# 🕒 Solar-Gregorian DateTime Converter for 32-bit RTC Counters

A lightweight and efficient C library to convert between Solar (Persian/Shamsi) and Gregorian date-time formats using only a 32-bit RTC counter.

## 📌 Overview

Many embedded systems and microcontrollers have a very limited RTC — often just a single 32-bit register counting seconds. This project offers a simple way to handle full date-time functionality (Gregorian ↔ Solar) with **second-level precision**, using **no extra hardware** and **minimal resources**.

---

## 🔧 Features

- 🔁 **Bidirectional conversion** between Gregorian and Solar (Jalali) calendars
- 📅 Supports **leap year** detection for both calendars
- ⏱️ Handles time in seconds (HH:MM:SS)
- 📆 Valid from `2022/03/21 (1401/01/01)` to `2157/12/29 (1536/10/08)`
- 💾 Designed for **bare-metal microcontrollers** with limited memory
- 🧮 Based on a single 32-bit counter (e.g., seconds since 1401/01/01)

---

## 📂 Files

- `datetime_converter.c` - Core conversion logic
- `main()` function - Example usage and test case
- No external libraries required

---

## 🚀 Usage

```c
DateTimeGregorian dtg;
dtg.year = 2157;
dtg.month = 12;
dtg.day = 29;
dtg.hour = 12;
dtg.minute = 0;
dtg.second = 0;

uint32_t seconds = Convert_DateTimeGregorian_Int32(dtg);  // Gregorian -> Seconds
DateTimeSolar dts = Convert_Int32_DateTimeSolar(seconds); // Seconds -> Solar
DateTimeGregorian dtgn = Convert_Int32_DateTimeGregorian(seconds); // Seconds -> Gregorian
```

## 📎 Online Demo

Try it online via OnlineGDB:
👉 https://onlinegdb.com/U5iSbmvYb






