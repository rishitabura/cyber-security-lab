import java.util.Scanner;

public class ecc {

    static class Point {
        int x;
        int y;

        public Point(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }

    static int p, a, b;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // input d
        System.out.print("Enter a: ");
        a = scanner.nextInt();
        // input e
        System.out.print("Enter b: ");
        b = scanner.nextInt();
        System.out.print("Enter p: ");
        p = scanner.nextInt();
        // input a point
        System.out.print("Enter x: ");
        int x = scanner.nextInt();
        System.out.print("Enter y: ");
        int y = scanner.nextInt();
        Point a1 = new Point(x, y);
        // validate point on the curve
        System.out.println("Check if point lies on the curve?");
        System.out.println(isPoint(a1));

        System.out.println("Adding points:");
        System.out.print("Enter xq: ");
        int x1 = scanner.nextInt();
        System.out.print("Enter yq: ");
        int y1 = scanner.nextInt();
        Point a3 = new Point(x1, y1);
        System.out.println("Sum:");
        a3 = addPoints(a1, a3);
        System.out.println(a3.x + " " + a3.y);

        System.out.print("Enter message (x, y) point x: ");
        int x2 = scanner.nextInt();
        System.out.print("Enter message (x, y) point y: ");
        int y2 = scanner.nextInt();
        Point Pm = new Point(x2, y2);
        System.out.print("Enter na (private key): ");
        int na = scanner.nextInt();
        Point[] result = encrypt(Pm, na);
        Point a3_encrypted = result[0];
        Point a4_encrypted = result[1];
        System.out.println("Encrypted message:");
        System.out.println("(" + a3_encrypted.x + ", " + a3_encrypted.y + "), (" + a4_encrypted.x + ", " + a4_encrypted.y + ")");
        Point a6 = decrypt(na, a3_encrypted, a4_encrypted);
        System.out.println("Decrypted message:");
        System.out.println(a6.x + " " + a6.y);
        // prints all points on the curve
        System.out.println("All Points on the curve are:");
        allPoints(p, a, b);
    }

    static boolean isPoint(Point a1) {
        int y = (a1.y * a1.y) % p;
        int x = (a1.x * a1.x * a1.x + a * a1.x + b) % p;
        return x == y;
    }

    static Point addPoints(Point a1, Point a3) {
        if (a1 == null || a3 == null) {
            return null;
        }
        if (a1.x == a3.x && a1.y != a3.y) {
            return a1;
        }
        if (a1.x == a3.x) {
            int l = ((3 * a1.x * a1.x + a) * inv(2 * a1.y)) % p;
            int xr = (l * l - 2 * a1.x) % p;
            int yr = (l * (a1.x - xr) - a1.y) % p;
            return new Point(xr, yr);
        } else {
            int l = ((a3.y - a1.y) * inv(a3.x - a1.x)) % p;
            int xr = (l * l - a1.x - a3.x) % p;
            int yr = (l * (a1.x - xr) - a1.y) % p;
            return new Point(xr, yr);
        }
    }
// Calculate modular inverse
static int inv(int n) {
    for (int i = 0; i < p; i++) {
        if ((n * i) % p == 1) {
            return i;
        }
    }
    return 0;
}
    static Point[] encrypt(Point Pm, int na) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter generator (i, j) coordinate i: ");
        int g = scanner.nextInt();
        System.out.print("Enter generator (i, j) coordinate j: ");
        int h = scanner.nextInt();
        Point genr = new Point(g, h);
        Point pa = genPA(na, genr);
        int k = 41;
        Point c1 = genPA(k, genr);
        Point c2 = genPA(k, pa);
        c2 = addPoints(c2, Pm);
        return new Point[]{c1, c2};
    }

    static Point genPA(int na, Point genr) {
        Point g2 = genr;
        for (int k = 1; k < na; k++) {
            g2 = addPoints(g2, genr);
        }
        return g2;
    }

    static Point decrypt(int na, Point a3, Point a4) {
        Point h1 = genPA(na, a3);
        h1.y = -1 * h1.y;
        return addPoints(a4, h1);
    }
    static void allPoints(int p, int a, int b) {
        for (int i = 0; i < p; i++) {
            for (int j = 0; j < p; j++) {
                Point a2 = new Point(i, j);
                if (isPoint(a2)) {
                    System.out.println("(" + i + ", " + j + ")");
                }
            }
        }
    }
}
