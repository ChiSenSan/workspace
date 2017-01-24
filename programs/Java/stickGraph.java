//stickGraph.java

import java.applet.*;
import java.awt.*;
import java.awt.event.*;
import java.util.Random;

public class stickGraph  extends  Applet  implements  ActionListener
{
	private Boolean paint = false;
	private TextField box = new TextField(5);
	private Button go = new Button(" ���s ");
	
	private Label str = new Label("�l�@�H�H");
	private Color[] colors = {Color.black, Color.blue, Color.yellow, Color.green, Color.red, Color.pink};
	
	int cnt = 0;
	int num[] = new int[10];
	int max = 10;
	public void init()
	{
        resize( 600 , 600 );
	    add( str ); 
	    add( box );
	    add( go );
        
        go.addActionListener( this ) ;
	}
	
	public void actionPerformed( ActionEvent e )
	{
		//if(cnt >= max-1){
			//�x��
		//}
		//else{
			String t = box.getText();
			num[cnt] = Integer.parseInt( t );
			cnt++;
			paint = true;
			repaint();
		//}
	}
	
	public void paint (Graphics g)
	{
		int x0 = 100;
		int y0 = 300;
		int counterX = 120;
		int counterY = 160;
		int g_size = 40;
		int val = 4;
		
		int i;
		
		//�O���t�n
		g.setColor(Color.black);
		g.drawLine(x0,150,x0,450);
		g.drawLine(x0,y0,g_size*11,y0);
		//�ڐ���n
		for(i=0; i<11; i++){
		int y = y0 + ((25-(i*5))*val);
			g.drawLine(x0+10,y0,x0,y0);
		}
		
		//�O���t�\���n
		if(paint){
			for(i=0; i<=cnt; i++){
				int x = x0+10+(g_size*i);
				int y = y0-(num[i]*val);
				
				g.setColor(colors[i%6]);
				g.fillRect(x, y, g_size, num[i]*val);
			}
		}
		showStatus(">>>>>>>>>>>>>>>�`��"+(cnt+1)+"��"+num[cnt-1]);
	}
}