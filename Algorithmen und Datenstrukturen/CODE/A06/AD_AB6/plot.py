from myplotmod import dlread, myloglog_tn

names = ['QS', 'QS+IS 5', 'QS+IS 10', 'QS+IS 15', 'QS+IS 20', 'QS+IS25', 'Keysort']

arr = dlread("move.txt", ";", True)
myloglog_tn(arr, 10, "moves", names)

arr = dlread("compare.txt", ";", True)
myloglog_tn(arr, 10, "compares", names)

arr = dlread("total.txt", ";", True)
myloglog_tn(arr, 10, "moves+compare", names)

arr = dlread("time.txt", ";", True)
myloglog_tn(arr, 10, "time_ms", names)