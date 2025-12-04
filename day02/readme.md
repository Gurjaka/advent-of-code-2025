# 🎄 Day 2: Gift Shop

You get inside and take the elevator to its only other stop: the gift shop.
"Thank you for visiting the North Pole!" gleefully exclaims a nearby sign.
You aren't sure who is even allowed to visit the North Pole, but you know you can access the lobby through here, and from there you can access the rest of the North Pole base.

As you make your way through the surprisingly extensive selection, one of the clerks recognizes you and asks for your help.

One of the younger Elves was playing on a gift shop computer and managed to add a whole bunch of invalid product IDs to their gift shop database.
Your job: identify which IDs are invalid.

The input consists of several **ranges** of product IDs. A range is written like:

```
11-22,95-115,998-1012,1188511880-1188511890,222220-222224,
1698522-1698528,446443-446449,38593856-38593862,565653-565659,
824824821-824824827,2121212118-2121212124
```

(ID ranges are separated by commas; each range is `start-end`.)

An **invalid ID** is any number that consists of **some sequence of digits repeated exactly twice**. Examples:

* `55` → `5` repeated twice
* `6464` → `64` repeated twice
* `123123` → `123` repeated twice

IDs have no leading zeroes.

For the example input, the invalid IDs would be:

* **11–22** → `11`, `22`
* **95–115** → `99`
* **998–1012** → `1010`
* **1188511880–1188511890** → `1188511885`
* **222220–222224** → `222222`
* **1698522–1698528** → none
* **446443–446449** → `446446`
* **38593856–38593862** → `38593859`
* Remaining ranges → none

> Adding up all the invalid IDs in this example produces 1227775554.

Your task: **sum all invalid IDs** in your puzzle input.

---

## Part Two

The clerk digs deeper and realizes there are **still** invalid IDs.
It turns out the young Elf was doing *more* patterns.

Now an ID is invalid if it is made from **any sequence of digits repeated two or more times**, not just exactly twice.

Examples:

* `12341234` → `1234` ×2
* `123123123` → `123` ×3
* `1212121212` → `12` ×5
* `1111111` → `1` ×7

Re-evaluating the example ranges:

* **11–22** → `11`, `22`
* **95–115** → `99`, `111`
* **998–1012** → `999`, `1010`
* **1188511880–1188511890** → `1188511885`
* **222220–222224** → `222222`
* **1698522–1698528** → none
* **446443–446449** → `446446`
* **38593856–38593862** → `38593859`
* **565653–565659** → `565656`
* **824824821–824824827** → `824824824`
* **2121212118–2121212124** → `2121212121`

> Adding up all the invalid IDs in this example produces 4174379265.

Your task: **sum all invalid IDs** using these updated rules.
