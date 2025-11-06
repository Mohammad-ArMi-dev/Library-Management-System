# Library Manager — Library Management System

**Version:** 1.1

## Project Overview

A simple Library Management System implemented in modern C++ (C++17).
The program provides a text-based menu to add members/books, borrow/return books, search and list records. Data is persisted in two plain text files (`books.txt`, `members.txt`). The system tracks per-book copy counts and how many copies are currently borrowed.

---

## Features

* Add / register a new member
* Add / register a new book (track copies in stock)
* Borrow a book (member can borrow up to 3 books)
* Return a book
* Track `borrowedCount` per book (how many copies are currently loaned out)
* Track which book IDs each member has borrowed
* List members and books (shows available copies = `copiesInStock - borrowedCount`)
* Search members by first name and books by title
* Save / load persistent data from plain text files

---

## Requirements

* C++17 (or later) compatible compiler (e.g. `g++`, `clang++`, MSVC)
* OS: Windows / Linux / macOS
* Console encoding: UTF-8 recommended (if using non-ASCII/Persian text)

---

## Build & Run

1. Put the source code into `main.cpp`.
2. Compile:

    ```bash
    g++ -std=c++17 -O2 -o library main.cpp
    ````

3. Run:

   * Linux/macOS:

        ```bash
        ./library
        ```

   * Windows (CMD / PowerShell):

        ```powershell
        library.exe
        ```

---

## File Structure

* `books.txt` — stores book records (one per line).
* `members.txt` — stores member records (one per line).

### `books.txt` format

Each line uses `|` separators and the fields are:

```txt
<id>|<title>|<author>|<copiesInStock>|<borrowedCount>
```

* `id` = integer book identifier
* `title` = book title (may contain spaces)
* `author` = author name
* `copiesInStock` = total copies the library owns (integer)
* `borrowedCount` = number of copies currently loaned out (integer)

**Example:**

```txt
1|The C++ Programming Language|Bjarne Stroustrup|5|2
2|Clean Code|Robert C. Martin|3|0
```

---

### `members.txt` format

Each line uses `|` to separate basic fields; after `birthYear` there may be a comma-separated list of borrowed book IDs:

```txt
<memberId>|<firstName>|<lastName>|<birthYear>[,<borrowedBookId1>,<borrowedBookId2>,...]
```

**Examples:**

```txt
1001|Ali|Salehi|1999,1,2
1002|Sara|Ahmadi|2000
```

---

## Menu / Usage

When running, the program shows a menu:

```txt
1. Register Member
2. Register Book
3. Checkout Book (borrow)
4. Checkin Book (return)
5. Print Members
6. Print Books
7. Find Member by First Name
8. Find Book by Title
0. Exit
```

---

## Limitations & Notes

* Plain text parsing is fragile; malformed lines can crash the program.
* `cin` / `getline` usage with multiple `cin.ignore()` calls may skip inputs.
* Single-user design; concurrent runs may corrupt files.
* No timestamps, authentication, or roles.
* `0 <= borrowedCount <= copiesInStock` should be maintained.

---

## Suggested Improvements (TODO)

1. Wrap `stoi` calls in `try/catch` to handle malformed lines.
2. Use JSON or SQLite instead of plain text files.
3. Refactor input handling without `goto`.
4. Implement case-insensitive or partial search.
5. Track borrow/return timestamps and history.
6. Improve UI prompts and error messages.
7. Add concurrency safety for multi-user access.

---

## Known Issues

* Multiple `cin.ignore()` calls before `getline` may skip inputs.
* `goto` in input loops complicates flow.
* `persistData()` overwrites files atomically — a crash may leave partial data.
* Previous docs incorrectly described `books.txt` as a single borrowed bit; current code uses `borrowedCount` and `copiesInStock`.

---

## Contributing & Branching

* Branch naming: `feature/<short-description>` or `fix/<short-description>`
* Commit example:

```txt
✅ fix: improve input validation in book and member registration

- Added reusable input checks
- Replaced goto loops with helper functions
- Ensured input buffer is properly cleared on failure
```

---

## License

MIT

---

## Author

Mohammad Mohammadi

---

## Persian Version — سیستم مدیریت کتابخانه

**نسخه:** 1.1

## شرح پروژه

این پروژه یک سیستم سادهٔ مدیریت کتابخانه به زبان C++17 است.
برنامه دارای منوی متنی است و امکانات زیر را فراهم می‌کند: افزودن عضو و کتاب، امانت دادن و بازگرداندن کتاب، جستجو و نمایش فهرست‌ها.
داده‌ها در دو فایل متنی (`books.txt` و `members.txt`) ذخیره می‌شوند و تعداد نسخه‌های کتاب‌ها و تعداد کتاب‌های قرض گرفته شده نیز مدیریت می‌شوند.

---

## ویژگی‌ها

* ثبت عضو جدید
* ثبت کتاب جدید (مدیریت تعداد نسخه‌ها)
* قرض دادن کتاب (حداکثر ۳ کتاب برای هر عضو)
* بازگرداندن کتاب
* پیگیری تعداد نسخه‌های قرض داده شده (`borrowedCount`) برای هر کتاب
* پیگیری شناسه کتاب‌هایی که هر عضو قرض گرفته است
* نمایش فهرست اعضا و کتاب‌ها (نسخه‌های موجود = `copiesInStock - borrowedCount`)
* جستجو بر اساس نام کوچک اعضا و عنوان کتاب
* ذخیره و بازیابی داده‌ها در فایل متنی

---

## پیش‌نیازها

* کامپایلر C++17 یا بالاتر (مانند `g++`، `clang++`)
* سیستم‌عامل: ویندوز / لینوکس / مک
* توصیه: UTF-8 برای متون فارسی

---

## کامپایل و اجرا

1. سورس کد را در `main.cpp` قرار دهید.
2. کامپایل:

    ```bash
    g++ -std=c++17 -O2 -o library main.cpp
    ````

3. اجرا:

   * لینوکس/مک:

        ```bash
        ./library
        ```

   * ویندوز:

        ```powershell
        library.exe
        ```

---

## ساختار فایل‌ها

* `books.txt` — اطلاعات کتاب‌ها (هر سطر یک کتاب)
* `members.txt` — اطلاعات اعضا (هر سطر یک عضو)

### فرمت `books.txt`

```txt
<id>|<title>|<author>|<copiesInStock>|<borrowedCount>
```

* `id` = شناسه کتاب
* `title` = عنوان کتاب
* `author` = نام نویسنده
* `copiesInStock` = تعداد کل نسخه‌ها
* `borrowedCount` = تعداد نسخه‌های قرض گرفته شده

**مثال:**

```txt
1|The C++ Programming Language|Bjarne Stroustrup|5|2
2|Clean Code|Robert C. Martin|3|0
```

---

### فرمت `members.txt`

```txt
<memberId>|<firstName>|<lastName>|<birthYear>[,<borrowedBookId1>,<borrowedBookId2>,...]
```

**مثال‌ها:**

```txt
1001|Ali|Salehi|1999,1,2
1002|Sara|Ahmadi|2000
```

---

## منو / نحوه استفاده

پس از اجرا، منو به صورت زیر نمایش داده می‌شود:

```txt
1. ثبت عضو
2. ثبت کتاب
3. قرض دادن کتاب
4. بازگرداندن کتاب
5. نمایش اعضا
6. نمایش کتاب‌ها
7. جستجوی عضو بر اساس نام کوچک
8. جستجوی کتاب بر اساس عنوان
0. خروج
```

---

## محدودیت‌ها و نکات

* پردازش فایل متنی ساده است و خطا در فرمت فایل ممکن است باعث کرش شود.
* استفاده از `cin.ignore()` و `getline()` ممکن است باعث رد شدن برخی ورودی‌ها شود.
* طراحی تک‌کاربره است و دسترسی همزمان پشتیبانی نمی‌شود.
* زمان و نقش‌های کاربری ثبت نمی‌شوند.
* `0 <= borrowedCount <= copiesInStock` باید رعایت شود.

---

## بهبودهای پیشنهادی (TODO)

1. اضافه کردن try/catch برای `stoi` و جلوگیری از کرش در صورت فایل خراب
2. استفاده از JSON یا SQLite به جای فایل متنی
3. حذف یا جایگزینی `goto` با حلقه‌های کنترل‌شده
4. پیاده‌سازی جستجوی بدون حساسیت به حروف یا جستجوی جزئی
5. ثبت تاریخ امانت و بازگشت
6. بهبود پیام‌های ورودی و خطا
7. اطمینان از همگام‌سازی داده‌ها در حالت چندکاربره

---

## مسائل شناخته‌شده

* چند `cin.ignore()` ممکن است ورودی را رد کند.
* `goto` در حلقه‌های ورودی، خوانایی را کاهش می‌دهد.
* `persistData()` فایل‌ها را به صورت کامل بازنویسی می‌کند و در صورت کرش ممکن است داده‌ها ناقص شوند.
* نسخه قبلی اسناد، `books.txt` را به عنوان یک بیت قرضی توضیح داده بود؛ اکنون `borrowedCount` و `copiesInStock` جایگزین شده‌اند.

---

## مشارکت و نسخه‌بندی

* نام شاخه‌ها: `feature/<توضیح کوتاه>` یا `fix/<توضیح کوتاه>`
* مثال کامیت:

```txt
✅ fix: بهبود اعتبارسنجی ورودی در ثبت کتاب و عضو

- اضافه کردن بررسی ورودی‌ها
- استفاده از توابع کمکی به جای goto
- پاکسازی بافر ورودی در صورت خطا
```

---

## مجوز

MIT

---

## نویسنده

محمد محمدی
