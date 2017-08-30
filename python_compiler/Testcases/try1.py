f=input("enter no")
beg=0
end=5
flag=0
while (beg<=end):
	mid=(end+beg)/2;
	if(list[mid]==f):
		print("found");
		flag=1;
		break;
	elif(list[mid]<f):
		beg=beg+1;
	else:
	    end=end-1;
if(flag==0):
    print("not found");
