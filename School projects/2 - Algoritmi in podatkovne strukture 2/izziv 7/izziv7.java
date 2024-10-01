import java.util.*;

public class izziv7{
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();

        //w^n = 1 -- koren enote
        //w^i != 1; 1<=i<n -- primitivni koren
        //w = e^(i*(2pi/n)) -- n-ti primitivni koren
        //w = cos(2pi/n)+i*sin(2pi/n) -- eulerjeva formula
        
        //2. w^k != 1 za k = 1,...,d-1. — w je primitivni koren enote
        //d==n


        //iscemo najmanjsi w da obstaja n-ti primitivni koren
        boolean neobstaja = true;
        int prast = 2;
        int prva = 0;
        while(neobstaja){
            int[] Z = new int[prast-1];
            for(int i = 1; i < prast; i++){
                Z[i-1] = i;
            }
            //izracunaj ce obstaja
            for(int i = 1; i < Z.length; i++){
                if(is_nth_prime_root(Z[i], prast, n)){
                    if(neobstaja){
                        System.out.printf("%d: ",prast);
                        neobstaja = false;
                        prva = Z[i];
                    }
                    
                    System.out.printf("%d ",Z[i]);
                };
            }
            if(!neobstaja){
                System.out.println();
                izpis_matrike(prva, prast, n);
            }
            //naslednje prast
            prast = naslednje_prastevilo(prast);
        } 
    }
    private static int pow(int st, int n, int p){
        if(n == 0)return 1;
        int x = st % p;
        for(int i = 0; i < n-1; i++){
            x = x * st % p;
        }
        return x;
    }
    private static void izpis_matrike(int w, int p, int n){
        int tab[][] = new int[n][n];
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                tab[i][j] = pow(w, i*j, p);
                //tab[i][j] = (int) Math.pow(w, i*j) % p;
            }
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                System.out.printf("%2d ",tab[i][j]);
            }
            System.out.println();
        }

    }
    private static boolean is_nth_prime_root(int st, int p, int n){
        //1<=i<n  w^i != 1

        //2----p-1 - st
        //st^n % p == 1 --> true
        int x = st;
        for(int i = 0; i < n-1; i++){
            if(x == 1)return false;
            x = (x * st) % p;
        }
        return x == 1;
    }
    private static int naslednje_prastevilo(int p){
        int st = 2;
        for(int i = p + 1; true; i++){
            boolean prast = true;
            for(int j = 2; j < (i/2); j++){
                if(i % j == 0)prast = false;
            }
            if(prast){
                st = i;
                break;
            }
        }
        return st;
    }
}