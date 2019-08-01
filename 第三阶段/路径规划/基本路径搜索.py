#grid format:
# 0 = navigable space
# 1 = occupied space
grid = [[0,1,0,0,0,0],
		[0,1,0,0,0,0],
		[0,1,0,0,0,0],
		[0,1,0,0,0,0],
		[0,0,0,0,0,0]]
heuristic = [[9,8,7,6,5,4],
             [8,7,6,5,4,3],
             [7,6,5,4,3,2],
             [6,5,4,3,2,1],
             [5,4,3,2,1,0]]
init = [0,0]
cost = 1
goal = [len(grid)-1,len(grid[0])-1]
delta = [[-1,0], # go up
		[0,-1],  #go left
		[1,0],	#go down
		[0,1]]	#go right
delta_name = ['^', '<', 'v', '>']

def search(grid,init,goal,cost):
	#openlistelementsareofthetype:[g,x,y]
    closed=[[0 for row in range(len(grid[0]))] for col in range(len(grid))]
    expand=[[-1 for row in range(len(grid[0]))] for col in range(len(grid))]
    action=[[-1 for row in range(len(grid[0]))] for col in range(len(grid))]
    closed[init[0]][init[1]]=1
    x=init[0]
    y=init[1]
    g = 0
    h = heuristic[x][y]
    f = g + h
    open = [[f,g,h,x,y]]
    found = False # flag that is set when search complete
    resign = False #flag set if we can't find expand
    count = 0
    print ('initial open list:')
    for i in range(len(open)):
        print(' ',open[i])
    print('----------')

    while found is False and resign is False:
        #check if we still have elements on the open list
        if len(open) == 0:
            resign = True
            print('fail')
            print('-----------------')
        #print '####'Search terminated without success
        else:
            #remove node from list
            open.sort()
            open.reverse()
            next = open.pop()
            #print 'take list item'
            print(next)
            x = next[3]
            y = next[4]
            g = next[1]
            expand[x][y] = count
            count += 1
            #check if we are done
            if x == goal[0] and y == goal[1]:
                found = True
                print(next)
                print('##########Search successful')
                print('-----------------')
            else:
                #expand winning element and add to new open list
                for i in range(len(delta)):
                    x2 = x + delta[i][0]
                    y2 = y + delta[i][1]
                    if x2 >= 0 and x2 < len(grid) and y2 >= 0 and y2 < len(grid[0]):
                        if closed[x2][y2] == 0 and grid[x2][y2] == 0:
                            g2 = g + cost
                            h2 = heuristic[x2][y2]
                            f2 = g2 + h2
                            open.append([f2,g2,h2,x2,y2])
                            print('append list item') 
                            print([g2,x2,y2])
                            print('-----------------')
                            closed[x2][y2] = 1
                            action[x2][y2] = i
                            
                    print ('new open list')
                    for i in range(len(open)):
                        print(' ',open[i])
                        
                    print('-----------------')
    policy = [[' ' for row in range(len(grid[0]))] for col in range(len(grid[1]))]
    x = goal[0]
    y = goal[1]
    policy[x][y] = '*'
    for i in range(len(expand)):
        print(expand[i])
    while x != init[0] or y != init[1]:
        x2 = x - delta[action[x][y]][0]
        y2 = y - delta[action[x][y]][1]
        policy[x2][y2] = delta_name[action[x][y]]
        x= x2
        y = y2
    for i in range(len(policy)):
        print(policy[i])
search(grid,init,goal,cost)
                
    
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
























