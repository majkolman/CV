import java.util.*;

public class naloga{
    public static void main(String[] args){
    Scanner sc = new Scanner(System.in);

    int vsota1 = 0;
    int vsota2 = 0;
    boolean neke = true;

    while(neke && sc.hasNextInt()){
        int a= sc.nextInt();
        
        if(a == 1){
            vsota1++;
        }else{
            vsota2++;
            vsota1--;
        }

        if(vsota1 < 0){
            System.out.println("BANKROT");
            neke = false;
            break;
        }

        
    }
    if(neke){
            System.out.printf("%d\n%d",vsota1,vsota2);
    }
}
}
