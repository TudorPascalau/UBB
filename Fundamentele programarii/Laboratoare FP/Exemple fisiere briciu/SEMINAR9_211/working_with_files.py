# # deschide fisier pentru citire
# f = open("persoane.txt", 'r')
# # line = f.readline()
# #
# # while line != "":
# #     print(line)
# #     line = f.readline()
#
# # lines = f.readlines()
# # print(type(lines))
# # print(lines)
#
# content = f.read()
# print(type(content))
# print(content)
# f.close()
#
# f = open("persoane.txt", "a")
# # f.write("\n3, Ajfsdfka")
# f.writelines(['11, fshdgafg\n', '22, dshgf\n'])
# f.close()

# l = ['11, fshdgafg', '22, dshgf']
# print(l)
# l = [element+"\n" for element in l]

# # l = [1, 2, 3, 4]
# # new_lst = [element**2 for element in l]
# # print(new_lst)
#
# def raise_to_power(x, n):
#     return x ** n
#
#
# l = [1, 2, 3, 4, 5, 6]
# new_lst = [raise_to_power(element, element) for element in l if element % 2 == 0]
# print(new_lst)

class MyError(Exception):
    pass

def f():
    raise MyError
f()