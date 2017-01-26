//stickGraph.java

import java.applet.*;
import java.awt.*;
import java.awt.event.*;

public class stickGraph  extends  Applet  implements  ActionListener
{
	private Boolean paint = false;
	private TextField box = new TextField(5);
	private Button go = new Button(" 実行 ");
	
	private Label str = new Label("値　？？");
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
		if(cnt >= max){
			//警告
		}
		else{
			String t = box.getText();
			num[cnt] = Integer.parseInt( t );
			cnt++;
			paint = true;
			repaint();
		}
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
		
		//グラフ系
		g.setColor(Color.black);
		g.drawLine(x0,150,x0,450);
		g.drawLine(x0,y0,g_size*(max+3),y0);
		//目盛り系
		for(i=0; i<11; i++){
			int y = y0 + ((25-(i*5))*val);
			String t = Integer.toString((i*5)-25);
			if(((i*5)-25) > 0) t = "+" + t;
			g.drawLine(x0-10,y,x0,y);
			g.drawString(t, x0-30, y);
		}
		
		//グラフ表示系
		if(paint){
			for(i=0; i<cnt; i++){
				int x = x0+10+(g_size*i);
				int y, y_size;
				if(num[i] >= 0){
					y = y0-(num[i]*val);
					y_size = num[i]*val;
				}
				else{
					y = y0;
					y_size = (-num[i]*val);
				}
				g.setColor(colors[i%6]);
				g.fillRect(x, y, g_size, y_size);
				
				g.setColor(Color.black);
				g.drawString((i+1)+"回", x+5,150);
			}
		}
		showStatus(">>>>>>>>>>>>>>>描画"+cnt+"回"+num[cnt-1]);
	}
}