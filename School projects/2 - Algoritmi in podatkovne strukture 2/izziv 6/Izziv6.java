import java.util.Scanner;
import java.util.*;


class Matrix {


	private int[][] m;

	public int n; //only square matrices

	public Matrix(int n){

		this.n = n;

		m = new int[n][n];

	}


    //set value at i,j
	public void setV(int i, int j, int val){

		m[i][j] = val;

	}


    // get value at index i,j
	public int v(int i, int j){

		return m[i][j];

	}


    // return a square submatrix from this
	public Matrix getSubmatrix(int startRow, int startCol, int dim){

		Matrix subM = new Matrix(dim);

		for (int i = 0; i<dim ; i++ )

			for (int j=0;j<dim ; j++ )

				subM.setV(i,j, m[startRow+i][startCol+j]);



		return subM;

	}


    // write this matrix as a submatrix from b (useful for the result of multiplication)
	public void putSubmatrix(int startRow, int startCol, Matrix b){

		for (int i = 0; i<b.n ; i++ )

			for (int j=0;j<b.n ; j++ )

				setV(startRow+i,startCol+j, b.v(i,j));

	}


    // matrix addition
	public Matrix sum(Matrix b){

		Matrix c = new Matrix(n);

		for(int i = 0; i< n;i++){

			for(int j = 0; j<n;j++){

				c.setV(i, j, m[i][j]+b.v(i, j));

			}

		}

		return c;

	}





    // matrix subtraction
	public Matrix sub(Matrix b){

		Matrix c = new Matrix(n);

		for(int i = 0; i< n;i++){

			for(int j = 0; j<n;j++){

				c.setV(i, j, m[i][j]-b.v(i, j));

			}

		}

		return c;

	}



	//simple multiplication
	public Matrix mult(Matrix b){
		Matrix c = new Matrix(n);

		for(int i = 0; i < n; i++){

			for(int j = 0; j < n; j++){

				for(int k = 0; k < n; k++){

					c.setV(i, j, (c.v(i, j) + m[i][k]*b.v(k, j)));

				}

			}

		}

		return c;
	}


    // Strassen multiplication
	public Matrix multStrassen(Matrix b, int cutoff){
		if(this.n <= cutoff){
			return this.mult(b);
		}

        Matrix C = new Matrix(n);

		Matrix a11 = this.getSubmatrix(0,0, n/2);
		Matrix a12 = this.getSubmatrix(0,n/2, n/2);
		Matrix a21 = this.getSubmatrix(n/2,0, n/2);
		Matrix a22 = this.getSubmatrix(n/2, n/2, n/2);

		Matrix b11 = b.getSubmatrix(0,0, n/2);
		Matrix b12 = b.getSubmatrix(0,n/2, n/2);
		Matrix b21 = b.getSubmatrix(n/2,0, n/2);
		Matrix b22 = b.getSubmatrix(n/2,n/2, n/2);

		Matrix m1 = (a11.sum(a22)).multStrassen((b11.sum(b22)), cutoff);	//a11+a22 * b11+b22
		Matrix m2 = (a21.sum(a22)).multStrassen((b11), cutoff);				//a21+a22 * b11
		Matrix m3 = (a11).multStrassen((b12.sub(b22)), cutoff);				//a11 * b12-b22
		Matrix m4 = (a22).multStrassen((b21.sub(b11)), cutoff);				//a22 * b21-b11
		Matrix m5 = (a11.sum(a12)).multStrassen((b22), cutoff);				//a11+a12 * b22
		Matrix m6 = (a21.sub(a11)).multStrassen((b12.sum(b11)), cutoff);	//a21-a11 * b12+b11
		Matrix m7 = (a12.sub(a22)).multStrassen((b21.sum(b22)), cutoff);	//a12-a22 * b21+b22

		m1.mprint("m1");
		m2.mprint("m2");
		m3.mprint("m3");
		m4.mprint("m4");
		m5.mprint("m5");
		m6.mprint("m6");
		m7.mprint("m7");

		Matrix c11 = m1.sum(m4).sub(m5).sum(m7);
		Matrix c12 = m3.sum(m5);
		Matrix c21 = m2.sum(m4);
		Matrix c22 = ((m1.sub(m2)).sum(m3)).sum(m6);

		C.putSubmatrix(0, 0, c11);
		C.putSubmatrix(0, n/2, c12);
		C.putSubmatrix(n/2, 0, c21);
		C.putSubmatrix(n/2, n/2, c22);

		return C;
	}

	public void print(){
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				System.out.printf("%d ", this.v(i, j));
			}
			System.out.println();
		}
	}

	public void mprint(String m){
		int count = 0;
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				count += this.v(i, j);
			}
		}
		System.out.printf("%s: %d\n",m,count);
	}

}




public class Izziv6{

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int cutoff = sc.nextInt();

		Matrix a = new Matrix(n);
		for(int i = 0; i < n ; i++){
			for(int j = 0; j < n; j++){
				a.setV(i, j, sc.nextInt());
			}
		}

		Matrix b = new Matrix(n);
		for(int i = 0; i < n ; i++){
			for(int j = 0; j < n; j++){
				b.setV(i, j, sc.nextInt());
			}
		}
		
		Matrix c = a.multStrassen(b, cutoff);
		c.print();

	}



}
