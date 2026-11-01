# ASSIGNMENT 2 – CO2

**Course:** DSA01 – C++ Programming  
**Student Name:** [Enter your name]  
**Register Number:** [Enter your register number]  
**GitHub Repository:** [Paste repository URL]  
**Compiler:** g++ 14.2.0 (update if your compiler differs)  

> Replace the bracketed personal details. Execute each program on your own computer and add genuine screenshots. The timing values are intentionally not pre-filled because they depend on your computer and compiler.

## Q1 – Call by Value, by Reference and by Pointer (6 Marks)

### Implementation and output
The program is in `Q1/Q1.cpp`. Call by value changes only a local copy. A reference is an alias for the caller's variable, and a pointer stores its address; dereferencing the pointer changes the original variable.

**Prediction for the PDF's given `change` program:**
```text
1 12 13
1 100
16 13 6
```

**Explanation:** `a` remains 1 because it is passed by value. `b` becomes 12 and `c` becomes 13 because the reference and pointer refer to the caller's objects. `bigger(a,c)=100` assigns to the larger object, which is `c` at that point. The `show` calls use `(y,z)=(5,10)`, then `z=10`, then no defaults, producing 16, 13 and 6.

**Completed-code expected output:**
```text
after call by value   : 45000
after call by reference: 40500
```

The value version receives an independent `long long`, so changing it does not update `hostelFee`. A `const Student&` is appropriate when a large object must be read without copying and must not be modified. All three parameter-passing versions take O(1) time for this arithmetic. Passing a `long long` by value copies one scalar; passing a large `Student` by value copies its members and any owned data, while reference and const-reference parameters pass an alias (typically pointer-sized).

**Design decision:** Return the revised fee when a calculation should be pure and easy to test or chain. Modify by reference when the purpose is explicitly to update the caller's stored fee. For several concessions, calculate the combined percentage/rules carefully and update once, avoiding repeated rounding surprises.

## Q2 – Return by Reference and Its Dangers (4 Marks)

`Q2/Q2.cpp` implements `highestMark`, which returns a reference to the largest array element. The caller can write `highestMark(marks,n) += 2` because the returned reference is an lvalue referring to that element. Finding the maximum takes O(n) time and O(1) extra space.

Returning a reference to a local variable is invalid because the local object is destroyed when the function returns. A compiler normally warns about returning a reference to a local variable; using the dangling reference has undefined behaviour. The unsafe function is included for warning demonstration and is deliberately not called.

- `int&`: caller can modify the original element.
- `const int&`: avoids a copy but prevents modification through that reference.
- `int`: returns an independent copy; changing it does not change the array.
- Index: return the maximum element's position, then use `marks[index]`.
- Pointer: return the element's address; check for null and respect lifetime.

A vector reallocation can invalidate references, pointers and iterators to its elements. An index is generally safer across reallocation, provided the logical element remains at that index. Re-finding the maximum remains O(n), and the search uses O(1) extra space.

## Q3 – Default Arguments and Function Overloading (6 Marks)

If overloads `charge(double)`, `charge(double,bool)` and `charge(double,bool=false,bool=false)` coexist, a call such as `charge(2.0)` can match more than one viable overload, causing ambiguity. The solution in `Q3/Q3.cpp` uses one double overload with rightmost default arguments, a distinct int overload for grams, and a `Parcel` overload.

**Six calls and predicted selection:**

| Call | Selected overload | Reason |
|---|---|---|
| `charge(2)` | `charge(int)` | exact int match |
| `charge(2.0)` | `charge(double,bool,bool)` | exact double match; defaults used |
| `charge(2.0f)` | double overload | float promotes to double |
| `charge(2000)` | int overload | exact int match (grams) |
| `charge(2.5,true)` | double overload | exact first parameter match |
| `charge(p)` | Parcel overload | exact Parcel reference match |

Overload resolution prefers an exact match over a promotion, and a promotion over a standard conversion. Default arguments must be supplied from the right because trailing parameters can be omitted only when their defaults are known. Adding a new option can be handled by extending the Parcel structure or its fields; a single configuration object can reduce overload growth. Overload resolution occurs at compile time and adds no runtime selection cost. The time for the charge arithmetic is O(1); passing Parcel by const reference avoids copying it.

## Q4 – Specifying a Class with an Array Inside It (6 Marks)

`Q4/Q4.cpp` defines `SavingsAccount` with private account number, balance, a fixed array of ten transaction strings, count and circular next index. `deposit`, `withdraw` and `miniStatement` are public. Some methods are defined outside the class using `SavingsAccount::`.

The array is private to protect the balance and transaction history from invalid external changes. When full, shifting requires O(k) assignments for k stored transactions. A circular index overwrites the oldest entry in O(1), using O(10) fixed storage. Increasing the requirement from ten to fifty changes the capacity constant and storage size; a circular buffer still needs only a small number of index/capacity changes.

A `std::deque` can use `push_back` and `pop_front` to keep the newest k items, with O(1) operations at the ends in typical complexity guarantees. A fixed circular array also offers O(1) insertion and predictable fixed memory. Both use O(k) storage.

## Q5 – Static Members and Arrays of Objects (7 Marks)

`Q5/Q5.cpp` uses static `issued` and `CAPACITY`, shared by every ticket. The static data member is defined once outside the class (`int BusTicket::issued = 0;`). Each object has its own `seat` and `name`. The static `count()` function can be called as `BusTicket::count()`; it has no `this` pointer and cannot directly access a particular object's non-static data.

**PDF prediction:** `101 103 104 4`. Three array elements are constructed first, receiving IDs 101–103; `extra` receives 104. `issued()` returns `next - 100`, which is 4. Thus the constructor runs four times.

**Completed-code expected output:**
```text
Asha: Seat 1
Bala: Seat 2
Chitra: Seat 3
Dev: Waiting
Issued: 3
```

An array of objects constructs each element, so the static count is shared and continues to increase across loops and function calls; it does not reset when a function returns. The global-variable alternative is simple but weakens encapsulation and risks name conflicts. A separate `TicketOffice` object makes it possible to manage two buses independently, with one counter per office. Both approaches take O(1) time and use O(1) counter storage.

## Q6 – Friend Functions and Inline Functions (8 Marks)

`Q6/Q6.cpp` declares `minutesBetween` and `earlier` as friends. They are non-member functions, called as `minutesBetween(a,b)`, but can access private `h` and `m` of both objects. A member function would be called through one object, such as `a.isEarlier(b)`. Friend functions are useful when an operation treats two operands symmetrically.

**Completed-code expected output:**
```text
205 false
```

The implementation converts each time to minutes after midnight. The absolute difference gives the number of minutes between two times; comparison of the total-minute values determines which is earlier. Additional tests include 11:55 versus 12:05 and identical times.

`inline` permits the compiler to substitute a function body at a call site, but it is a request/permission rather than a guarantee. The compiler may inline or not inline based on optimisation and function properties. Making fields public would weaken encapsulation. Getters or member functions can preserve private data; a friend function provides direct access but increases coupling. Each calculation is O(1) time and O(1) space. The source includes a 10,000,000-call inline versus non-inline benchmark. Compile and run it with both `-O0` and `-O2`; record your own timings because results depend on compiler, CPU and optimisation.

## Q7 – Diagnose, Redesign and Validate (13 Marks)

### A. Diagnose the limitation
The original fixed-array history design shifts all k stored elements when a new transaction arrives after capacity is reached. This is O(k) work per insertion when full. The selected redesign targets this repeated shifting.

### B. Design objective
Keep only the latest ten values and reduce each full-buffer insertion from O(k) element moves to O(1) writes, without increasing the fixed storage capacity.

### C. Revised solution
The original `ShiftHistory` stores values from index zero and shifts each value left when full. `CircularHistory` stores a `next` index, writes at that position, advances it modulo capacity, and overwrites the oldest value. Both use ten integers (O(k) storage). The circular design adds one index variable and makes chronological traversal slightly more involved.

**Pseudocode:**
```text
add(value):
    data[next] = value
    next = (next + 1) modulo capacity
    if count < capacity: count = count + 1
```

### D. Prediction
For a large number of insertions, the circular version should perform fewer data assignments after the buffer becomes full. Both should retain the same most recent value and use constant time per insertion in the circular case.

### E. Implementation and validation
Run `Q7/Q7.cpp` with the same input count for both implementations. It inserts one million sequential values and prints the last value and measured insertion times. Both last values should be `999999`. Record the actual microsecond values from your own execution and attach a terminal screenshot. Compile with the same compiler and optimisation flags for a fair comparison.

### F. Final evaluation
The circular buffer meets the objective if the measured insertion time is lower while producing the same retained newest value. It uses O(1) insertion and O(k) fixed storage. The shifting design is simpler to inspect and can be preferable for very small histories or when chronological array order is more important than insertion speed. Timing can vary due to optimisation, CPU scheduling and cache effects; the asymptotic difference is the reliable design argument.

## Build and run
From the repository root, compile each task separately:
```bash
g++ -std=c++17 -Wall -Wextra Q1/Q1.cpp -o q1
./q1
```
Replace `Q1/Q1.cpp` and `q1` with the relevant task path/name for Q2–Q7. On Windows, run the generated `.exe` file instead of `./q1`.

## Evidence checklist
- [ ] Add your name, register number and GitHub URL.
- [ ] Compile and run every Q1–Q7 program yourself.
- [ ] Add output screenshots inside the corresponding task folder.
- [ ] For Q2, capture the compiler warning for the intentionally unsafe local-reference example.
- [ ] For Q6, measure 10,000,000 calls using `-O0` and `-O2`, and record actual results if required by your faculty.
- [ ] For Q7, record the actual timing values from the same machine and compiler settings.
- [ ] Commit each task separately or progressively as required by the PDF.
