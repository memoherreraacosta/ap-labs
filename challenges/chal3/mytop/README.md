MyTop
=====
Implement a new version of the `top` tool. The only source of information about processes  will be the `/proc` filesystem. This should be a real-time application that automatically updates the dashboard with new and terminated processes. Below more details about the requirements.


Sample mytop output
-------------------
```
# ./mytop
| PID   | Parent | Name           | State    | Memory | # Threads | Open Files |
|-------|--------|----------------|----------|--------|-----------|------------|
| 120   | 1      | sshd           | Active   | 120M   | 1         | 5          |
| 3453  | 120    | sshd-child     | Sleeping | 4M     | 1         | 0          |
| 433   | 433    | single-process | Active   | 15M    | 2         | 1          |
| 3434  | 34     | multi-threads  | Active   | 1020M  | 4         | 5          |
| 16887 | 16886  | test-app       | Sleeping | 17M    | 1         | 7          |
```

To Build
--------------------

```
	$ make
```


To Run
-------------------

```
	$ sudo ./mytop
```	
