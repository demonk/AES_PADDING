package cn.demonk.aes;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Base64;
import android.widget.TextView;

import javax.crypto.Cipher;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("xxxxxx");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        final String src = "qwertyuiopasdfghjklzxcvbnm";
        byte[] result = encrypt(src.getBytes());
        String encodeStr = new String(Base64.encode(result, Base64.DEFAULT));

        TextView tv = findViewById(R.id.sample_text);
        tv.setText(encodeStr);

        String decryptStr = decrypt(encodeStr);
        tv.setText(decryptStr);

    }

    private String decrypt(String be) {
        try {
            final String KEY = "abcdefghijklmnop";//16bytes
            final String IV = "0123456789abcdef";//16bytes

            SecretKeySpec skeySpec = new SecretKeySpec(KEY.getBytes(), "AES");
            Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
            IvParameterSpec iv = new IvParameterSpec(IV.getBytes());
            cipher.init(Cipher.DECRYPT_MODE, skeySpec, iv);
            byte[] encrypted1 = Base64.decode(be, Base64.DEFAULT);
            byte[] original = cipher.doFinal(encrypted1);
            String originalString = new String(original);
            return originalString;
        } catch (Exception e) {

        }
        return "";
    }

    private native byte[] encrypt(byte[] src);
}
