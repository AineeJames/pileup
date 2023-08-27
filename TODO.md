# TODO:
- Fixes
```
Loop is almost certainly messed up
Adding to token index wayy too much
```

- Memory:
```
mem // pointer to the start of memory
mem 1 + // pointer to (start of memory) + 1 byte

mem 69 + 10 store // stores 10 into mem[69]
mem 10 + load     // loads mem[10] to top of stack
```

- Loops should work more like this maybe:
```
while condition {
  // loop contents
}

// example loop that print from 0 to 99
0 while dupe 100 < {
  dupe print
  1 +
}
```

- If / else:
```
if condition {
  // ran if condition == 1
} else {
  //ran if condition == 0
}

if 10 10 = {
  69 print
} else {
  420 print
}
```

- Functions could look like this:
```
func identifier {
  // function contents
}

func print_add {
  + print
}

220 200 print_add
35 34 print_add
```

- Main entrypoint:
```
func main {
  // do stuff here...
}
```
