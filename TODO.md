# TODO:

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
```

- If / else:
```
condition if {
  // ran if condition == 1
} else {
  //ran if condition == 0
}
```

- Functions could look like this:
```
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
