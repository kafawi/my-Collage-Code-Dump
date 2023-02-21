from myplotmod import dlread, myloglog_tn

arr = dlread("sample.txt", ";", True)
names = ['best tree, worst sarch','best tree, bes search', 'random', 'worst tree (list)']
myloglog_tn(arr, 2, "Suchbaum.sumBetween(0, N)", names)

