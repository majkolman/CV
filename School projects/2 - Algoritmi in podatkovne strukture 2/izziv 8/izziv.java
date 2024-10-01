import java.util.*;


public class izziv{

    
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int ex;
        for(ex = 1; n > ex; ex *= 2);
        ex*= 2;
        double tab1[] = new double[ex];
        double tab2[] = new double[ex];

        for(int i = 0; i < n; i++){
            tab1[i] = sc.nextDouble();
        }

        for(int i = 0; i < n; i++){
            tab2[i] = sc.nextDouble();  
        }
        Complex p1[] = FFT(tab1, ex);
        Complex p2[] = FFT(tab2, ex);

        Complex res[] = new Complex[p1.length];

        for(int i = 0; i < p1.length; i++){
            res[i] = p1[i].times(p2[i]);
        }
        Complex fin[] = FFTinverz(res, ex);
        for(int i = 0; i < fin.length; i++){
            fin[i] = fin[i].times(1.0 / fin.length);
            System.out.print(fin[i].toString() + " ");
        }
        System.out.println();
    }

    public static Complex[] FFT(double[] a, int d){
        if(d == 1){
            Complex a0[] = new Complex[1];
            a0[0] = new Complex(a[0], 0);
            return a0;
        }else{
            double a_S[] = new double[d/2]; 
            int ps = 0;
            double a_L[] = new double[d/2];
            int pl = 0;
            for(int i = 0; i < d; i++){
                if(i % 2 == 0){
                    a_S[ps++] = a[i];
                }else{
                    a_L[pl++] = a[i];
                }
            }
            Complex p_S[] = FFT(a_S, d/2);
            Complex p_L[] = FFT(a_L, d/2);

            Complex p[] = new Complex[d];
            Complex wk = new Complex(1, 0);
            Complex w = new Complex(0, 2*Math.PI/d).exp();
            for(int k = 0; k < p.length / 2; k++){
                p[k] = p_S[k].plus(wk.times(p_L[k]));
                p[k+d/2] = p_S[k].minus(wk.times(p_L[k]));
                wk = wk.times(w);
            }
            for(int i = 0; i < p.length; i++){
                System.out.print(p[i].toString() + " ");
            }
            System.out.println();

            return p;
        }
    }
    public static Complex[] FFTinverz(Complex[] a, int d){
        if(d == 1){
            return a;
        }else{
            Complex a_S[] = new Complex[d/2]; 
            int ps = 0;
            Complex a_L[] = new Complex[d/2];
            int pl = 0;
            for(int i = 0; i < d; i++){
                if(i % 2 == 0){
                    a_S[ps++] = a[i];
                }else{
                    a_L[pl++] = a[i];
                }
            }
            Complex p_S[] = FFTinverz(a_S, d/2);
            Complex p_L[] = FFTinverz(a_L, d/2);

            Complex p[] = new Complex[d];
            Complex wk = new Complex(1, 0);
            Complex w = new Complex(0, -2*Math.PI/d).exp();
            for(int k = 0; k < p.length / 2; k++){
                p[k] = p_S[k].plus(wk.times(p_L[k]));
                p[k+d/2] = p_S[k].minus(wk.times(p_L[k]));
                wk = wk.times(w);
            }
            for(int i = 0; i < p.length; i++){
                System.out.print(p[i].toString() + " ");
            }
            System.out.println();

            return p;
        }
    }
}

class Complex{
    double re;
    double im;

    public Complex(double real, double imag) {
        re = real;
        im = imag;
    }

    public String toString() {
        double tRe = (double)Math.round(re * 100000) / 100000;
        double tIm = (double)Math.round(im * 100000) / 100000;
        if (tIm == 0) return tRe + "";
        if (tRe == 0) return tIm + "i";
        if (tIm <  0) return tRe + "-" + (-tIm) + "i";
        return tRe + "+" + tIm + "i";
    }

    public Complex conj() {
        return new Complex(re, -im);
    }

    // sestevanje
    public Complex plus(Complex b) {
        Complex a = this;
        double real = a.re + b.re;
        double imag = a.im + b.im;
        return new Complex(real, imag);
    }

    // odstevanje
    public Complex minus(Complex b) {
        Complex a = this;
        double real = a.re - b.re;
        double imag = a.im - b.im;
        return new Complex(real, imag);
    }

    // mnozenje z drugim kompleksnim stevilo
    public Complex times(Complex b) {
        Complex a = this;
        double real = a.re * b.re - a.im * b.im;
        double imag = a.re * b.im + a.im * b.re;
        return new Complex(real, imag);
    }

    // mnozenje z realnim stevilom
    public Complex times(double alpha) {
        return new Complex(alpha * re, alpha * im);
    }

    // reciprocna vrednost kompleksnega stevila
    public Complex reciprocal() {
        double scale = re*re + im*im;
        return new Complex(re / scale, -im / scale);
    }

    // deljenje
    public Complex divides(Complex b) {
        Complex a = this;
        return a.times(b.reciprocal());
    }

    // e^this
    public Complex exp() {
        return new Complex(Math.exp(re) * Math.cos(im), Math.exp(re) * Math.sin(im));
    }


    //potenca komplesnega stevila
    public Complex pow(int k) {

        Complex c = new Complex(1,0);
        for (int i = 0; i <k ; i++) {
            c = c.times(this);
        }
        return c;
    }

}