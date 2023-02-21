from myplotmod import dlread, myloglog_tn

arr = dlread("sample.txt", ";", True)
names = ['recursive','iterative', 'binomial']
myloglog_tn(arr, 2, "Pascal's triangle", names)

