import optparse
from itertools import repeat

class EulerException(Exception):
    pass

def calc_polynomial(x, coefs):
    """ Pass coefs in order [cN, cN-1, ..., c1, c0] """
    return reduce(lambda value, coef: coef + x * value, reversed(coefs), 0)

def task_polynomial(x):
    return calc_polynomial(x, [(-1)**i for i in range(11)])

def equal(x, y, EPS=1e-2):
    return abs(x - y) < EPS

def build_lagrange_interpolation(data_points):
    """ Returns function of one arg, returning the value
        of Lagrange interpolation polynomial, which is build
        on data_points, in arg. data_points are a list of
        tuples [(x_i, y_i)].
    """
    data_points.sort()
    degree = len(data_points) - 1
    for i in range(degree):
        if data_points[i][0] == data_points[i +  1][0]:
            raise EulerException(
                    "Don't be stupid! All x-es should be distinct")
    def interpolation(x):
        for point in data_points:
            if equal(point[0], x):
                return point[1]
        result = 0
        for ipoint in data_points:
            basis_value = 1.0
            for jpoint in data_points:
                if ipoint[0] != jpoint[0]:
                    basis_value *= (x - jpoint[0])
                    basis_value /= (ipoint[0] - jpoint[0])
            result += basis_value * ipoint[1]
        return result
    return interpolation

def check_build_lagrange_interpolation():
    data = []
    def f(x):
        return x * x * x + x * x * 5 - 10
    for i in range(0, 4):
        data.append((i, f(i)))
    interpolation = build_lagrange_interpolation(data)
    for i in range(0, 8):
        assert(equal(interpolation(i), f(i)))
    data = []
    for i in range(1, 12):
        data.append((i, task_polynomial(i)))
    interpolation = build_lagrange_interpolation(data)
    for i in range(1, 14):
        assert(equal(interpolation(i), task_polynomial(i)))

def main():
    check_build_lagrange_interpolation()
    data = []
    bops = []
    for i in range(1, 11):
        data.append((i, task_polynomial(i)))
        interpolation = build_lagrange_interpolation(data)
        original_value, interpolated_value = \
                            task_polynomial(i + 1), interpolation(i + 1)
        assert(not equal(original_value, interpolated_value))
        bops.append(interpolated_value)
    print "FITs sum", sum(bops)

if __name__ == "__main__":
    main()
