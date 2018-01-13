import java.math.BigInteger;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class rsa{
    private static BigInteger p,q,factor,totient,publicKey,privateKey;
    private static Map<BigInteger,Character> map = new HashMap<>();
    
    static void setup(){
        p = new BigInteger("61");
        q = new BigInteger("53");
        factor = p.multiply(q);
        totient = (p.subtract(BigInteger.ONE)).multiply(q.subtract(BigInteger.ONE)); 
        /*boolean flag = false;
        for(int i = 2;!flag;i++)
        {
            BigInteger tmp = BigInteger.valueOf(i);
            BigInteger g = tmp.gcd(totient);
            if(g.compareTo(BigInteger.ONE) == 0) 
            {
                publicKey = tmp;
                flag = true;
            }
        }
        
        privateKey = ((BigInteger.valueOf(15)).multiply(totient)).add( BigInteger.ONE );
        privateKey = publicKey.divide(publicKey);*/
        
        publicKey = BigInteger.valueOf(17);
        privateKey = BigInteger.valueOf(2753);
    }
    
    static void _status(){
        System.out.println("\np = " + p + "\nq = " + q + " \nfactor = " + factor + "\ntotient = " + totient);
        System.out.println("\npublicKey = " + publicKey + "\nprivateKey = " + privateKey);
    }
    
    private static void map_setup(Map<BigInteger,Character> map){
        for(int i = 32;i < 127;i++) map.put(BigInteger.valueOf(i),(char)i);
        
        //for(int i = 32;i < 127;i++) System.out.println("map ( " + i + " ) = " + map.get(BigInteger.valueOf(i)));
    }
    
    public static BigInteger [] encrypt(String message){
        BigInteger [] array = new BigInteger [message.length()];
        map_setup(map);
        
        for(int i = 0;i < message.length();i++){
            BigInteger tmp = BigInteger.valueOf((int)message.charAt(i));
            tmp = tmp.modPow(publicKey, factor);
            array[i] = tmp;
        }
        
        System.out.println("\nThe Cipher Text :");        
        for(int i = 0;i < array.length;i++) System.out.print(array[i] + " ");
        System.out.println();
        
        return array;
    }
    
    public static void decrypt(BigInteger [] array){
        Character [] arr = new Character [array.length];
        
        for(int i = 0;i < array.length;i++){
            BigInteger tmp = array[i].modPow(privateKey, factor);
            arr[i] = map.get(tmp);
        }
        
        System.out.println("\nThe Recovered Plain Text :");        
        for(int i = 0;i < array.length;i++) System.out.print(arr[i]);
        System.out.println();
    }
    
    public static void main(String [] args){
        Scanner bt = new Scanner( System.in );
        setup();
        //_status();
        System.out.print("Give the message : ");
        String message = bt.nextLine();
        BigInteger [] array = new BigInteger [message.length()];array = encrypt(message);
        
        System.out.println("\n\nDo you want to decrypt the message (1/0)");
        int choice = bt.nextInt();
        if(choice == 1) decrypt(array);
        bt.close();
    }
}
