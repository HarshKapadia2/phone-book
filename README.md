# Phone Book

A simple command-line implementation of a persistent phone book in C to re-familiarize myself with the basics of C.

> NOTE:
>
> -   The program might contain some unnecessary code constructs, but they were added to familiarize myself with them.
> -   Sample phone record format in [phone-book-records.sample.txt](phone-book-records.sample.txt).
> -   Credits to [Siddharth Bhatia](https://github.com/welding-torch) for making me aware of [github.com/Alkaison/Projects-in-C](https://github.com/Alkaison/Projects-in-C#5-phonebook---code-here).

## Execution Instructions

In the project's root directory, please execute the following commands:

```shell
$ gcc phone-book.c -o pb
$ ./pb
```

The above commands can be executed in [Gitpod](https://gitpod.io) as well:

[![Open in Gitpod](https://gitpod.io/button/open-in-gitpod.svg)](https://gitpod.io/#https://github.com/HarshKapadia2/phone-book)

## Features

-   ✔️ Add a phone record
-   ✔️ Display all phone records
-   ✔️ Find a phone record based on an e-mail
-   ❌ Find phone record(s) based on a first name
-   ❌ Delete a phone record
-   ❌ Update a phone record
-   ✔️ Display phone book command help

## Sample Program

> Executed in Gitpod.

```bash
gitpod /workspace/phone-book (main) $ gcc phone-book.c -o pb
gitpod /workspace/phone-book (main) $ ./pb
Phone Book

Use 'pb help' for usage.

$ pb help
Usage: pb [TYPE] [FLAG]... [DATA]...
Use the phone book to add, update, delete or find records.

NOTE:
- e-mail IDs are unique, so duplicate e-mail IDs are not allowed.
- Commands are whitespace-sensitive, so data should not contain whitespaces.

Actions:
- Display all records: pb display
- Add a record: pb add <first_name> <last_name> <unique_email> <phone_number>
- Find a record using an e-mail: pb find -e <email_of_record_to_find>
- (To do) Update a record: pb update <first_name> <last_name> <email_of_record_to_update> <phone_number>
- (To do) Delete a record: pb delete <email_of_record_to_delete>
- (To do) Find record(s) using a first name: pb find -n <first_name_of_records_to_find>
- Exit phone book: pb exit
- Display command help: pb help

Eg:
pb add selena gomez sg@selenagomez.com +1(xxx)xxx-xxxx

$ pb add selena gomez sg@selenagomez.com +1(xxx)xxx-xxxx
Record added to phone book.

$ pb find -e sg@selenagomez.com
First name: selena
Last name: gomez
e-mail: sg@selenagomez.com
Phone no.: +1(xxx)xxx-xxxx

$ pb add lucas scheppingen
Insufficient number of parameters passed. Expected 4 parameter(s), but got 2. Use 'pb help' for usage.
The phone record could not be added to the phone book.

$ pb add lucas scheppingen lbl@laidbackluke.com +1xxxxxxxxxx
Record added to phone book.

$ pb display
First name: selena
Last name: gomez
e-mail: sg@selenagomez.com
Phone no.: +1(xxx)xxx-xxxx
---
First name: lucas
Last name: scheppingen
e-mail: lbl@laidbackluke.com
Phone no.: +1xxxxxxxxxx
---

$ pb exit
Phone book shut down.
gitpod /workspace/phone-book (main) $
```
