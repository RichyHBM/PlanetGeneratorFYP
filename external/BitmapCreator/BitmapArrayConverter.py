import sys

impF = True
if( len(sys.argv) != 2 ):
    print ("Please supply just the C array file.")
    impF = False


def threeDig(i):
    if(len(i) == 4): return i
    elif(len(i) == 3): return "0" + i
    elif(len(i) == 2): return "00" + i
    elif(len(i) == 1): return "000" + i
    else: return "0000"

if(impF):
    try:
        orfile = open(sys.argv[1])
        myLine = orfile.readline()
        positions = []
        for i in range(0, 256):
            myLine = orfile.readline()
            myLine = myLine[2:len(myLine)-3]
            numbers = myLine.split(',')
            tup = (threeDig(numbers[0]) ,threeDig(numbers[1][1:]), threeDig(numbers[2]), threeDig(numbers[3]))
            positions.append( tup )
            
        orfile.close()
        outFile = open(sys.argv[1] + ".txt", 'w')
        for i in range(0, 256):
            outFile.write(positions[i][0] + " " + positions[i][1] + " " + \
                          positions[i][2] + " " + positions[i][3] + "\n")
        outFile.close()
        
    except Exception as e:
        print ("Failed to convert." , e)
    
