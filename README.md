# Assignment-1
 LPA* and D* Lite on C++

1.0 Introduction
2.0 Algorithm Information
3.0 Skeletal Code
4.0 SnapShots
5.0 Tabulation of Results
6.0 Discussion
7.0 User Guide
	

1.0 Introduction 

Intelligent artificial systems are utilised in many different technologies and industries to achieve specific duties. Machine vision, robots, machine learning, object identification are such areas where intelligent systems are widely used. It is important to understand such technologies to further refine and improve their capabilities for important situations.

This report will be specifically looking into the development and testing of intelligent algorithms that are capable of traversing a path with a start and end goal which may or may not have obstacles on the way. Lifelong Planning and D* Lite were the two algorithms that were chosen and developed for this assignment. 

2.0 Algorithm Information

Most of the data structures utilized in this assignment were already in the skeletal framework. I did not add new data structures to my algorithms. The main default data structure that was present and utilized was the vector structure. The vector structure was capable of handling the information within the cells. This includes the start and goal cells, successors and predecessors, the g and rhs values etc. The other data structure that was used is the heap type which is used for the priority queue.

The logic that was displayed by the pseudocode from the lectures was followed and implemented step by step. The initialise function was edited from the original to make it more flexible. On top of the i and j values from the maze, the move, predecessor and link cost were initialized for reference. 

Functions were created to traverse through the cells in the grid mathematically for both the successors and predecessors. This was done using if and else statements to compare the x,y and type values of each cell and using the rows and columns as boundaries.  A function for identifying the predecessors of each cell was also computed with similar logic as the D* lite requires the information of the predecessors for the algorithm to run.

The main function has keys enabled for F7. F8, F11, F12  D and A keys to enable the respectful functions. A timer function is within the main function to record the total time it took for the algorithm to reach the end destination. Int keys were also created in the class to record the values for state space, vertex count and path distance. 

The rest of the code followed the step by step logic that was already in the pseudo code which was the update vertex, finding the shortest path and main functions. The display path function was edited for both LPA and D*Lite. 

3.0 Skeletal Code

![image](https://user-images.githubusercontent.com/73975745/129876069-993bcabd-9de5-4c6f-8c99-bd5cfa2cf7d0.png)

![image](https://user-images.githubusercontent.com/73975745/129876085-950c2f61-5832-4006-ba94-15f1f9713229.png)

This code continues this cycle for all 8 directions. It will take too much space to post the entire function as it basically repeats the logic for each respective direction.

![image](https://user-images.githubusercontent.com/73975745/129876105-8e23db58-0ae1-4101-8f2a-c090b6936e7d.png)

![image](https://user-images.githubusercontent.com/73975745/129876125-d477629e-9882-488a-8869-e625f0da8392.png)

![image](https://user-images.githubusercontent.com/73975745/129876137-3fdabe42-08ae-4dfb-b12f-94dbae17bb2f.png)

![image](https://user-images.githubusercontent.com/73975745/129876155-25afb0ab-1b36-405c-9650-b1730c622c20.png)

![image](https://user-images.githubusercontent.com/73975745/129876164-9cf613fc-d64c-4768-849b-111be55e0778.png)

![image](https://user-images.githubusercontent.com/73975745/129876172-045575fe-54bc-40ac-9b5d-0b3bf8dd0e22.png)

![image](https://user-images.githubusercontent.com/73975745/129876180-dbfb55aa-5101-494c-a370-bb9561244349.png)

![image](https://user-images.githubusercontent.com/73975745/129876198-308911f7-77f7-4f9d-bb0f-605b98ce4ed5.png)

Main function calling the LPA star algorithm.

![image](https://user-images.githubusercontent.com/73975745/129876236-18b87b53-efba-497f-b059-d26ec55482f0.png)

![image](https://user-images.githubusercontent.com/73975745/129876251-beb5002c-9fdd-4c18-bc88-3bad0251dc05.png)

Find the shortest path function for LPAStar. 

![image](https://user-images.githubusercontent.com/73975745/129876304-84f16848-1457-48f4-a7e3-6979889da233.png)

![image](https://user-images.githubusercontent.com/73975745/129876318-77e8286f-03d8-4cf2-a372-541129ecbcff.png)

The D* Lite’s skeletal code is not posted with screencaps as it will take a lot of space and the majority of the code is very similar to the LPA planning algorithm. The logic has been changed around from the pseudocode to suit D* Lite. 

4.0 SnapShots

Grid LPA Journal
![image](https://user-images.githubusercontent.com/73975745/129876364-357ffb54-3e0a-47ae-bfde-a7a0b218fda0.png)

![image](https://user-images.githubusercontent.com/73975745/129876381-ddb3d86b-8809-4401-a044-f317a1fed83a.png)

![image](https://user-images.githubusercontent.com/73975745/129876392-8da6185d-6d65-4c67-a9a9-4cb5ff9b86d1.png)

![image](https://user-images.githubusercontent.com/73975745/129876406-5cfb9e58-3abd-4632-aff6-28667fec15e9.png)

Grid LPA Journal Big

![image](https://user-images.githubusercontent.com/73975745/129876429-ecc84013-8e86-41d6-adca-92288486a5ec.png)

![image](https://user-images.githubusercontent.com/73975745/129876443-4d23815c-4f04-497f-8021-2ff2478ad093.png)

![image](https://user-images.githubusercontent.com/73975745/129876466-07356f49-302f-41f2-8e19-06a25b97b3f6.png)

![image](https://user-images.githubusercontent.com/73975745/129876479-c78c3259-80ac-47e0-bdfa-8f16496986ad.png)

Grid Dstar Journal 

![image](https://user-images.githubusercontent.com/73975745/129876500-fdf2b336-0784-4582-9785-194b382ba2fb.png)

![image](https://user-images.githubusercontent.com/73975745/129876511-59681a66-5ec8-448e-8509-ef2fa4498f60.png)

![image](https://user-images.githubusercontent.com/73975745/129876522-64ec1ed7-3de5-4f47-b6e4-529b3cee6da0.png)

![image](https://user-images.githubusercontent.com/73975745/129876544-2fb0e686-3d37-4696-9815-d97b0e495c47.png)


5.0 Tabulations of Results

![image](https://user-images.githubusercontent.com/73975745/129876623-d3948c39-f66a-4160-b230-07e09b9a1d14.png)


6.0 Discussion

The LPA algorithm seems to be working perfectly as I could not find any mistakes or bugs when I was testing it out on grids.  The D* Lite is also working perfectly but I encountered bugs and errors when I was testing the replanning algorithm. The replanning portion would not respond during certain test cases and this would be due to simple error and logic malfunctions within the algorithm. Overall, the algorithm works well but if it was too perfect and precise, a lot more time and work would be required to identify all the bugs and errors within the algorithm. Another reason is probably because I followed the basic D* Lite pseudocode and not the final version. My algorithm is lacking the constant K value and theoretically, that constant K value plays a heavy role in increasing efficiency from the LPA algorithm.

Another issue is the GUI restarts after the first run and I believe this error is due to the initialize function being called twice within the main function. I attempted with the removal of one of the initialize functions but the entire would not work after the removal so I reversed my actions and left both initializations in place.  The start cell is also very buggy as the display disappears if it is chosen before the goal cell. To combat this, it is recommended that the goal cell is selected before the start cell.

For my tabulated results, I am not sure if my numbers are fitting and answering the context is asked for. I only tested both my algorithms for the spiral grid. On my first test, it took over a minute for the D* Lite to find the shortest path while it took much less for the LPA. However on my second try, both algorithms had a very similar time at around 0.0031 and 0.0034 seconds respectively. The other differences in numbers is that the D* Lite has half the number of vertexes accessed and close to half the number of state expansions when compared to LPA. The path length is the same for both but the max queue length is shorter for the D* Lite. These values show that the D* Lite was more efficient at tracing the shortest path for the spiral grid. This also follows the theoretical side of the algorithms as the D* Lite is a refined and upgraded version that is built off the LPA. The values would also have a higher disparity if the constant K was included within the D* Lite’s algorithm which would further demonstrate the increased efficiency of the D* Lite’s algorithm when compared to the LPA.

7.0 User Guide

F4 = Hide details
F5 = Show details
F7 =  Choose LPA Planning algorithm
F8 = Choose D* Lite algorithm
F9 = Copy display map to algorithm data structure
F10 = Run Search
F11 = Replanning for D* Lite algorithm
F12 = Replanning for LPA planning algorithm
D = Display shortest path for D*lite algorithm (follow up from F8)
A = Display shortest path for LPA planning algorithm (follow up from F7)
H = display heuristic values
B = Block a cell
U = Unblock a cell
K = Display key values
S = Set start goal
X = Set end goal

The grid map is changed around by accessing the properties file on the shortcut of the main.exe. The heuristic is also swapped around with the same method.


![image](https://user-images.githubusercontent.com/73975745/129876660-1cde78f1-7bd0-41f6-bb7a-a6250934dbb8.png)

The set start goal function is very buggy and only displays when the end goal is already constructed. For effective use, set the end goal before the start goal. From my testing, the program seems to work despite the start cell not being displayed.
