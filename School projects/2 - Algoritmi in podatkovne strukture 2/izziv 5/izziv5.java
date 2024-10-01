import java.util.*;

public class izziv5{
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int[] tab = new int[10];
        int dolzina = 0;
        for(int i = 0; sc.hasNext(); i++){
            if(i >= tab.length)tab = povecaj(tab);
            tab[i] = sc.nextInt();
            dolzina++;
        }
        int[] tab2 = new int[dolzina];
        System.arraycopy(tab, 0, tab2, 0, dolzina);
        tab = null;
        strnjeno_podzap(tab2, 0, dolzina - 1);
    }
    private static int[] povecaj(int[] tab){
        int[] tab2 = new int[tab.length * 2];
        System.arraycopy(tab, 0, tab2, 0, tab.length);
        return tab2;
    }
    private static int strnjeno_podzap(int[] tab, int l, int d){
        if(d <= l){
            printtab(tab, l, d, tab[l]);
            return tab[l];
        }
        int s = (d-l)/2+l;
        int maxl = strnjeno_podzap(tab, l, s);
        int maxd = strnjeno_podzap(tab, s+1, d);
        
        int pl = s;
        int pd = s + 1;
        int maxs = tab[pl] + tab[pd];
        int current_sum = maxs;
        while(pl > l){
            pl--;
            current_sum += tab[pl];
            if(current_sum > maxs)maxs = current_sum;
        }
        current_sum = maxs;
        while(pd < d){
            pd++;
            current_sum += tab[pd];
            if(current_sum > maxs)maxs = current_sum;
        }

        int max = Math.max(maxl,Math.max(maxd, maxs));
        printtab(tab, l, d, max);

        return max;
    }
    private static void printtab(int[] tab, int l, int d, int max){
        System.out.print("[");
        for(int i = l; i < d; i++){
            System.out.printf("%d, ", tab[i]);
        }
        System.out.printf("%d]: %d\n",tab[d] , max);
    }
}