
Enter length of reference string: 5

Enter the reference string: 1 2 3 2 1

Enter number of frames: 2

Choose Algorithm:

1. FIFO

2. LRU

3. Optimal

Step 1: 1 - PF 1 → [1, -]  

Step 2: 2 - PF 2 → [1, 2]  

Step 3: 3 - PF 3 → [3, 2] (replace 1, oldest)  

Step 4: 2 - no PF → [3, 2]  

Step 5: 1 - PF 4 → [1, 2] (replace 3)  

Total Page Faults (FIFO) = 4

Step 1: 1 - PF 1 → [1, -]  

Step 2: 2 - PF 2 → [1, 2]  

Step 3: 3 - PF 3 → [3, 2] (replace 1, least recently used)  

Step 4: 2 - no PF → [3, 2]  

Step 5: 1 - PF 4 → [1, 2] (replace 3, least recently used)  

Total Page Faults (LRU) = 4

Step 1: 1 - PF 1 → [1, -]  

Step 2: 2 - PF 2 → [1, 2]  

Step 3: 3 - PF 3 → [3, 2] (replace 1, used farthest in future)  

Step 4: 2 - no PF → [3, 2]  

Step 5: 1 - PF 4 → [1, 2] (replace 3, not used again)  

Total Page Faults (Optimal) = 4
