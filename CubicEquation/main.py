import math
import sys


class CubicEquation:
    a: float
    b: float
    c: float
    d: float

    def __init__(self, a, b, c, d):
        self.a = a
        self.b = b
        self.c = c
        self.d = d

    def _w(self) -> float:
        return -self.b / (3 * self.a)

    def _p(self) -> float:
        w = self._w()
        return (3 * self.a * w**2 + 2 * self.b * w + self.c) / self.a

    def _q(self) -> float:
        w = self._w()
        return (self.a * w**3 + self.b * w**2 + self.c * w + self.d) / self.a

    def _delta(self) -> float:
        p = self._p()
        q = self._q()
        return q**2 / 4 + p**3 / 27

    def solve(self) -> list[float]:
        delta = self._delta()
        q = self._q()
        w = self._w()

        if delta > 0:
            u = math.cbrt(-q / 2 + math.sqrt(delta))
            v = math.cbrt(-q / 2 - math.sqrt(delta))
            return [u + v + w]

        if delta == 0:
            x1 = w - 2 * math.cbrt(q / 2)
            x2 = w + math.cbrt(q / 2)
            return [x1, x2]

        p = self._p()
        mp3 = math.sqrt(-p / 3)
        fi = math.acos(3 * q / (2 * mp3))

        x1 = w + w * mp3 * math.cos(fi / 3)
        x2 = w + w * mp3 * math.cos(fi / 3 + 2 * math.pi / 3)
        x3 = w + w * mp3 * math.cos(fi / 3 + 4 * math.pi / 3)

        return [x1, x2, x3]


args = sys.argv[1:]
if len(args) != 4:
    print("ERROR: wrong number of arguments", file=sys.stderr)
    sys.exit(1)

args = list(map(float, args))

params = CubicEquation(args[0], args[1], args[2], args[3])
for i, x in enumerate(params.solve()):
    print(f"x{i} = {x} ")
