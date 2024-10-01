import java.util.Random;
public class primerjanje_brez_risanja{
    public static void main(String[] args){
        long X = 5100;
        long Y = 525;
        StdDraw.setXscale(0,102000 + X);
        StdDraw.setYscale(0,10500 + Y);
        StdDraw.setPenColor(StdDraw.BLACK);
        StdDraw.line(0, Y, 102000+X, Y);//x
        StdDraw.line(X, 0, X, 10500+Y);//y
        System.out.println("   n     |    linearno  |   dvojisko   |");
        System.out.println("---------+--------------+---------------");
        long tlp = 0;
        long tbp = 0;
        long tl = 0;
        long tb = 0;
        for(int i = 1000; i <= 100000; i += 1000){
            if(i != 1000){
                tlp = tl;
                tbp = tb;
            }
            tl = timeLinear(i);
            tb = timeBinary(i);
            StdDraw.setPenColor(StdDraw.BLACK);
            StdDraw.line(i-1000+X, tlp+Y, i+X, tl+Y);
            StdDraw.setPenColor(StdDraw.BLUE);
            StdDraw.line​(i-1000+X, tbp+Y, i+X, tb+Y);
            if(i < 10000){
                System.out.print("    ");
            }else if(i < 100000){
                System.out.print("   ");
            }else{
                System.out.print("  ");
            }
            System.out.print(i);
            if(tl < 1000){
                System.out.print(" |          ");
            }else if(tl < 10000){
                System.out.print(" |         ");
            }else{
                System.out.print(" |        ");
            }
            System.out.print(tl);
            if(tb < 1000){
                System.out.print(" |           ");
            }else if(tb < 10000){
                System.out.print(" |          ");
            }
            System.out.print(tb);
            System.out.println();
        }
    }
    public static int findLinear(int[] a, int v){
        for(int i = 0; i < a.length; i++){
            if(a[i] == v){
                return i;
            }
        }
        return 0;
    }
    public static int findBinary(int[] a, int l, int r, int v){
        if (r >= l) {
            int middle = l + (r - l) / 2;
            if (a[middle] == v) {
                return middle;
            }
            if (a[middle] > v) {
                return findBinary(a, l, middle - 1, v);
            }
            return findBinary(a, middle + 1, r, v);
        }
        return -1; // Return -1 if the element is not found
    
    }
    public static int[] generateTable(int n){
        int[] t = new int[n];
        for(int i = 0; i < n; i++){
            t[i] = i+1;
        }
        return t;
    }
    public static long timeLinear(int n){
        int[] t = generateTable(n);
        Random random = new Random();
        long startTime = System.nanoTime();
        for(int i = 0; i < 10000; i++){
            int x = random.nextInt(n-1);
            findLinear(t, x);
        }
        return (System.nanoTime() - startTime) / 10000;
    }
    public static long timeBinary(int n){
        int[] t = generateTable(n);
        Random random = new Random();
        long startTime = System.nanoTime();
        for(int i = 0; i < 1000000; i++){
            int x = random.nextInt(n-1);
            findBinary(t, 0, t.length, x);
        }
        return (System.nanoTime() - startTime) / 1000000;
    }
}