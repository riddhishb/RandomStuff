//Input:Image I, Message m   
//Output:Image J     
                

for each bit b of m                
    c:= next DCT coefficient from I   
    while c = 0 or c= 1  
        c := next DCT coefficient from I  
    end while   
    c := c mod 2 + b  
    replace coefficient in I by c  
end for                  