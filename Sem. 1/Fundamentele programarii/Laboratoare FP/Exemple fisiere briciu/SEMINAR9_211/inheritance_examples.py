class A:
    def __init__(self):
        self._x = 28


class B(A):
    def __init__(self):
        super().__init__()
        self.__y = 83

    def process(self):
        return self._x + self.__y


b = B()
print(b.process())

class MyError(Exception):
    pass

raise MyError