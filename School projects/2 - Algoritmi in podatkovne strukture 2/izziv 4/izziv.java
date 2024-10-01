import java.util.*;
public class izziv{
    static int counter_primerjave = 0;
    static int counter_zamenjave = 0;
    public static void main(String[] args){
        
        System.out.printf("Cas\tSorted\t\tRandom\t\tZamenjave Sorted Random\t\tPrimerjave Sorted Random\n");
        for(int n = 4; n <= 9; n++){
            int[] t1 = ustvari_tabelo(n);
            int[] t2 = ustvari_tabelo_rnd(n);
            
            counter_primerjave = 0;
            counter_zamenjave = 0;
            long cas1 = System.nanoTime();
            dualPivotQuickSort(t1, 0, t1.length-1);
            cas1 = System.nanoTime() - cas1;
            int zamenjave1 = counter_zamenjave;
            int primerjave1 = counter_primerjave;

            counter_primerjave = 0;
            counter_zamenjave = 0;
            long cas2 = System.nanoTime();
            dualPivotQuickSort(t2, 0, t2.length-1);
            cas2 = System.nanoTime() - cas2;
            int zamenjave2 = counter_zamenjave;
            int primerjave2 = counter_primerjave;

            System.out.printf("%4d\t%8d\t%6d\t\t%4d\t%4d\t%4d\t\t%4d\t%7d\t%5d\n", t1.length, cas1, cas2, t1.length, zamenjave1, zamenjave2, t1.length, primerjave1, primerjave2);
        }
    }

    private static void dualPivotQuickSort(int[] t, int left, int right) {
        counter_primerjave++;
        if(right - left >= 1){
            int p = Math.min(t[left], t[right]);
            int q = Math.max(t[left], t[right]);
            int l = left + 1;
            int g = right - 1;
            int k = l;

            
            while(k <= g){
                counter_primerjave++;
                if(t[k] < p){
                    counter_primerjave++;
                    counter_zamenjave++;
                    int temp = t[k];
                    t[k] = t[l];
                    t[l] = temp;
                    l++;
                }else if(t[k] >= q){
                    counter_primerjave++;
                    while(t[g] > q && k < g){
                        counter_primerjave++;
                        counter_primerjave++;
                        g--;
                    }
                    if(t[g] > q){
                        counter_primerjave++;
                    }
                    counter_primerjave++;
                    counter_zamenjave++;
                    int temp = t[k];
                    t[k] = t[g];
                    t[g] = temp;
                    g--;
                    if(t[k] < p){
                        counter_zamenjave++;
                        int x = t[k];
                        t[k] = t[l];
                        t[l] = x;
                        l++;
                    }
                    counter_primerjave++;
                }
                counter_primerjave++;
                counter_primerjave++;
                k++;
            }
            counter_primerjave++;
            g++;
            l--;
            t[left] = t[l]; t[l] = p;
            t[right] = t[g]; t[g] = q;
            dualPivotQuickSort(t, left, l - 1);
            dualPivotQuickSort(t, l + 1, g - 1);
            dualPivotQuickSort(t, g + 1, right);
        }
    }

    private static int[] ustvari_tabelo_rnd(int n) {
        int[] t = new int[2<<n];
        Random rand = new Random();
        for(int i = 0; i < t.length; i++){
            t[i] = rand.nextInt(2<<n);
        }
        return t;
    }

    private static int[] ustvari_tabelo(int n) {
        int[] t = new int[2<<n];
        for(int i = 0; i < t.length; i++){
            t[i] = i+1;
        }
        return t;
    }

    private static void print_tab(int[] t){
        for(int i = 0; i < t.length; i++) System.out.printf("%d ",t[i]);
        System.out.println(); 
    }
    
}