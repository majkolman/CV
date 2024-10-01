import java.util.Stack;

public class izziv3{
    static long stevec = 0;
    static int sHeight = 0;
    public static void main(String[] args){
        for(int n = 1; n < 19; n++){
            for(int k = 0; k < n; k++){
                //konstante za primer
                int dolzina_tab = (int) Math.pow(2, n);
                int st_cet = (int) Math.pow(2,k);
                int dolzina_cet = dolzina_tab / st_cet;
                //izdelaj ceto, ki se bo ponavljala
                int[] a = new int[dolzina_cet];
                for(int i = 1; i <= dolzina_cet; i++){
                    a[i-1] = i;
                }
                //izdelaj tabelo
                int[] tab = new int[dolzina_tab];
                int p = 0;
                for(int i = 0; i < dolzina_tab; i++, p++){
                    if(p >= a.length){
                        p = 0;
                    }
                    tab[i] = a[p];
                }
                //oprabi timsort na tabelo
                stevec = 0;
                Timsort(tab);
                System.out.print(stevec);
                System.out.print(" ");
            }
            System.out.println();
        }
        System.out.println(sHeight);
    }
    public static void Timsort(int[] tab){
        //ustvari stack z cetami
        int prejsni = -1;
        Stack<Ceta> S = new Stack<>();
        Ceta a = new Ceta(null);
        for(int i = 0; i < tab.length; i++){
            if(i != 0){
                stevec++;
            }
            if(tab[i] > prejsni){
                a.dodaj(tab[i]);
                prejsni = tab[i];
            }else{
                S.push(a);
                a = new Ceta(null);
                a.dodaj(tab[i]);
                prejsni = tab[i];
            }
        }
        S.push(a);
        int b = S.size();
        if(b > sHeight){
            sHeight = b;
        }
        //obdelaj stack
        Stack<Ceta> R = new Stack<>();
        
        while(!S.empty()){
            Ceta top = S.pop();
            R.push(top);
            S.pop();
            while(true){
                //elementi primera
                int h = R.size();
                Ceta r1 = R.peek();
                R.pop();
                Ceta r2 = null;
                Ceta r3 = null;
                Ceta r4 = null;
                if(!R.empty()){
                    r2 = R.peek();
                    R.pop();
                    if(!R.empty()){
                        r3 = R.peek();
                        R.pop();
                        if(!R.empty()){
                            r4 = R.peek();
                            R.pop();
                        }
                    }
                }
                //logika po pseudokodi
                if(h >= 3 && r1.dolzina > r3.dolzina){
                    r2 = r2.zlij(r3);
                    if(h >= 4){
                        R.push(r4);
                    }
                    R.push(r2);
                    R.push(r1);
                }else if(h >= 2 && r1.dolzina >= r2.dolzina){
                    r1 = r1.zlij(r2);
                    if(h >= 4){
                        R.push(r4);
                        R.push(r3);
                    }else if(h >= 3){
                        R.push(r3);
                    }
                    R.push(r1);
                }else if(h >= 3 && r1.dolzina + r2.dolzina >= r3.dolzina){
                    r1 = r1.zlij(r2);
                    if(h >= 4){
                        R.push(r4);
                    }
                    R.push(r3);
                    R.push(r1);
                }else if(h >= 4 && r2.dolzina + r3.dolzina >= r4.dolzina){
                    r1 = r1.zlij(r2);
                    R.push(r4);
                    R.push(r3);
                    R.push(r1);
                }else{
                    if(h >= 4){
                        R.push(r4);
                        R.push(r3);
                        R.push(r2);
                        R.push(r1);
                    }else if(h >= 3){
                        R.push(r3);
                        R.push(r2);
                        R.push(r1);
                    }else if(h >= 2){
                        R.push(r2);
                        R.push(r1);
                    }else if(h >= 1){
                        R.push(r1);
                    }
                    break;
                }
            }
        }
        while(R.size() > 1){
            Ceta r1 = R.peek();
            R.pop();
            Ceta r2 = R.peek();
            R.pop();
            r1 = r1.zlij(r2);
            R.push(r1);
        }
        R.pop();
    }
    public static class Ceta{
        private int[] elementi;
        private int dolzina;
        public Ceta(int[] elementi){
            if(elementi != null){
                this.elementi = elementi;
                this.dolzina = elementi.length;
            }else{
                this.elementi = null;
                this.dolzina = 0;
            }
        }
        public void dodaj(int a){
            if(this.elementi == null){
                this.elementi = new int[2];
            }
            if(this.dolzina >= this.elementi.length){
                //povecaj
                int[] newelementi;
                if(this.elementi.length == 0){
                    newelementi = new int[1];
                }else{
                    newelementi = new int[this.elementi.length * 2];
                }
                System.arraycopy(this.elementi, 0, newelementi, 0, this.elementi.length);
                this.elementi = newelementi;
            }
            this.elementi[this.dolzina] = a;
            this.dolzina++;
        }
        public Ceta zlij(Ceta ceta2){
            int[] e = {};
            Ceta rezultat = new Ceta(e);
            int p1 = 0;
            int p2 = 0;
            while(this.dolzina > 0 || ceta2.dolzina > 0){
                if(this.dolzina != 0 && ceta2.dolzina != 0){
                    stevec++;
                }
                if(this.dolzina > 0 && ceta2.dolzina > 0 && this.elementi[p1] < ceta2.elementi[p2]){
                    rezultat.dodaj(this.elementi[p1]);
                    this.dolzina--;
                    p1++;
                }else if(this.dolzina > 0 && ceta2.dolzina > 0 &&this.elementi[p1] > ceta2.elementi[p2]){
                    rezultat.dodaj(ceta2.elementi[p2]);
                    ceta2.dolzina--;
                    p2++;
                }else if(ceta2.dolzina == 0){
                    rezultat.dodaj(this.elementi[p1]);
                    this.dolzina--;
                    p1++;
                }else{
                    rezultat.dodaj(ceta2.elementi[p2]);
                    ceta2.dolzina--;
                    p2++;
                }
            }
            ceta2 = null;
            return rezultat;
        }
        public void print(){
            for(int i = 0; i < this.dolzina; i++){
                System.out.print(this.elementi[i]);
                System.out.print(" ");
            }
            System.out.println();
        }
    }
}