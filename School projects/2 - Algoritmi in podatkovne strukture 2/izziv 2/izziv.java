import java.util.Random;

public class izziv{
    static int counter = 0;
    public static int[] generateTableRand(int n){
        int[] t = new int[n];
        Random rand = new Random();
        for(int i = 0; i < n; i++){
            t[i] = rand.nextInt(n);
        }
        return t;
    }
    public static int[] generateTableSort(int n){
        int[] t = new int[n];
        for(int i = 0; i < n; i++){
            t[i] = i+1;
        }
        return t;
    }
    public static int findFirst(int[] t, int r, int s){
        return r;
    }
    public static int findRand(int[] t, int r, int s){
        Random rand = new Random();
        return r + rand.nextInt(s - r + 1);
    }
    public static int findMiddleRand(int[] t, int r, int s){
        Random rand = new Random();
        int a = r + rand.nextInt(s - r + 1);
        int b = r + rand.nextInt(s - r + 1);
        int c = r + rand.nextInt(s - r + 1);
        counter += 2;
        if(a == b){
            return b;
        }
        if(b == c){
            return b;
        }
        if((a < b && b < c) || (c < b && b < a)){
            return b;
        }else if((b < a && a < c) || (c < a && a < b)){
            return a;
        }else{
            return c;
        }
    }
    public static int findMedian(int[] t, int r, int s){
        int dolzina = s - r + 1;
        int[][] tabela = new int[dolzina][5];
        int j = 0;
        int i = r;
        int k = 0;
        while(i <= s){
            if(j == 5){
                j = 0;
                k++;
            }
            tabela[k][j] = t[i];
            j++;
            i++;
        }
        int[] mediane = new int[dolzina];
        for(int l = 0; l < tabela.length; l++){
            if(tabela[l][4] != 0){
                mediane[l] = Quicksort(tabela[l], 0, 4, 2, 1);
            }else{
                mediane[l] = tabela[l][0];
            }
        }
        int p = Quicksort(mediane, 0, mediane.length -1 , mediane.length / 2, 1);
        //najdi index p ja
        for(int l = r; l < s; l++){
            if(t[l] == p) return l;
        }
        return r;
    }

    public static int Quicksort(int[] t, int r, int s, int k, int pivot_select){
        int i = r;
        int j = s+1;
        int p = 0;
        int pivot_index = 0;
        switch (pivot_select) {
            case 1:
                pivot_index = findFirst(t, r, s);
                p = t[pivot_index];
                break;
            case 2:
                pivot_index = findRand(t, r, s);
                p = t[pivot_index];
                t[pivot_index] = t[r];
                t[r] = p;               
                break;
            case 3:
                pivot_index = findMiddleRand(t, r, s);
                p = t[pivot_index];
                t[pivot_index] = t[r];
                t[r] = p;
                break;
            case 4:
                pivot_index = findMedian(t, r, s);
                p = t[pivot_index];
                t[pivot_index] = t[r];
                t[r] = p;
                break;
        
            default:
                break;
        }
        if(s <= r) return p;
        //razdeli
            while(true){
                while(t[++i] < p){
                    counter++;
                    if(i == s){
                        counter++;
                        break;
                    }
                    counter++;
                }
                counter++;
                while(p < t[--j]){
                    counter++;
                    if(j == r){
                        counter++;
                        break;
                    }
                    counter++;
                }
                counter++;
                if(j <= i){
                    counter++;
                    break;
                }
                int temp = t[i];
                t[i] = t[j];
                t[j] = temp;
            }
            int x = t[r];
            t[r] = t[j];
            t[j] = x;
        //
        if(j > k){
            counter++;
            return Quicksort(t, r, j-1, k, pivot_select);
        }else if(j < k){
            counter++;
            return Quicksort(t, j+1, s, k, pivot_select);
        }else{
            counter += 2;
            return t[k];
        }
    }
    public static void main(String[] args){
        int[][] izpisi = new int[10][8];
        int ind = 0;
        for(int n = 100; n <= 100000; n = n * 10){
            int countSort1 = 0;
            int countSort2 = 0;
            int countSort3 = 0;
            int countSort4 = 0;

            int countRand1 = 0;
            int countRand2 = 0;
            int countRand3 = 0;
            int countRand4 = 0;

            //generiraj urejeno tabelo
            int[] sorted = generateTableSort(n);
            Random rand = new Random();

            //generiraj indekse za iskane elemente
            int[] find = new int[n/10];
            for(int i = 0; i < find.length; i++){
                find[i] = rand.nextInt(n);
            }

            //izracunaj st primerjav za urejeno tabelo
            for(int i = 0; i < find.length; i++){
                int[] t = sorted;
                counter = 0;
                Quicksort(t, 0, sorted.length - 1, find[i], 1);
                countSort1 += counter;
                t = sorted;
                counter = 0;
                Quicksort(t, 0, sorted.length - 1, find[i], 2);
                countSort2 += counter;
                t = sorted;
                counter = 0;
                Quicksort(t, 0, sorted.length - 1, find[i], 3);
                countSort3 += counter;
                t = sorted;
                counter = 0;
                Quicksort(t, 0, sorted.length - 1, find[i], 4);
                countSort4 += counter;
            }
            countSort1 /= find.length;
            countSort2 /= find.length;
            countSort3 /= find.length;
            countSort4 /= find.length;

            //izracunaj st primerjav za nakljucne tabele
            for(int j = 0; j < 10; j++){
                int[] random = generateTableRand(n);
                for(int i = 0; i < find.length; i++){
                    int[] t = random;
                    counter = 0;
                    Quicksort(t, 0, t.length - 1, find[i], 1);
                    countRand1 += counter;
                    t = random;
                    counter = 0;
                    Quicksort(t, 0, t.length - 1, find[i], 2);
                    countRand2 += counter;
                    t = random;
                    counter = 0;
                    Quicksort(t, 0, t.length - 1, find[i], 3);
                    countRand3 += counter;
                    t = random;
                    counter = 0;
                    Quicksort(t, 0, t.length - 1, find[i], 4);
                    countRand4 += counter;
                }
                countRand1 /= find.length;
                countRand2 /= find.length;
                countRand3 /= find.length;
                countRand4 /= find.length;
            }
            countRand1 /= 10;
            countRand2 /= 10;
            countRand3 /= 10;
            countRand4 /= 10;
            
            izpisi[ind][0] = countSort1;
            izpisi[ind][1] = countSort2;
            izpisi[ind][2] = countSort3;
            izpisi[ind][3] = countSort4;
            izpisi[ind][4] = countRand1;
            izpisi[ind][5] = countRand2;
            izpisi[ind][6] = countRand3;
            izpisi[ind][7] = countRand4;
            ind++;
        }
        System.out.println("SORTED");
        System.out.println("\r\n" + "10^2\t10^3\t10^4\t10^5");
        System.out.printf("%d\t%d\t%d\t%d\n",izpisi[0][0],izpisi[1][0],izpisi[2][0],izpisi[3][0]);
        System.out.printf("%d\t%d\t%d\t%d\n",izpisi[0][1],izpisi[1][1],izpisi[2][1],izpisi[3][1]);
        System.out.printf("%d\t%d\t%d\t%d\n",izpisi[0][2],izpisi[1][2],izpisi[2][2],izpisi[3][2]);
        System.out.printf("%d\t%d\t%d\t%d\n",izpisi[0][3],izpisi[1][3],izpisi[2][3],izpisi[3][3]);

        System.out.println("RANDOM");
        System.out.println("\r\n" + "10^2\t10^3\t10^4\t10^5");
        System.out.printf("%d\t%d\t%d\t%d\n",izpisi[0][4],izpisi[1][4],izpisi[2][4],izpisi[3][4]);
        System.out.printf("%d\t%d\t%d\t%d\n",izpisi[0][5],izpisi[1][5],izpisi[2][5],izpisi[3][5]);
        System.out.printf("%d\t%d\t%d\t%d\n",izpisi[0][6],izpisi[1][6],izpisi[2][6],izpisi[3][6]);
        System.out.printf("%d\t%d\t%d\t%d\n",izpisi[0][7],izpisi[1][7],izpisi[2][7],izpisi[3][7]);
    }
}