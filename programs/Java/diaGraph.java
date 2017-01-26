//diaGraph.java

import java.applet.*;
import java.awt.*;
import java.awt.event.*;

public class diaGraph  extends  Applet  implements  ActionListener
{
	private Boolean paint = false;
	private TextField name_box = new TextField(7);
	private TextField eng_box = new TextField(5);
	private TextField jap_box = new TextField(5);
	private TextField math_box = new TextField(5);
	private TextField sci_box = new TextField(5);
	
	private Label name_str = new Label("ñºëO");
	private Label eng_str = new Label("âpåÍ");
	private Label jap_str = new Label("çëåÍ");
	private Label math_str = new Label("êîäw");
	private Label sci_str = new Label("óùâ»");
	
	private Button go = new Button("é¿çs");
	
private Color[] colors = {Color.red, Color.blue, Color.yellow, Color.green, Color.black, Color.gray, Color.pink};
	
	int cnt = 0;
	int max = 7;
	
	String names[] = new String[7];
	int eng_num[] = new int[7];
	int jap_num[] = new int[7];
	int math_num[] = new int[7];
	int sci_num[] = new int[7];
	
	public void init()
	{
		resize( 800 , 700 );
		add( name_str ); add( name_box );
		add( eng_str );  add( eng_box );
		add( jap_str );  add( jap_box );
		add( math_str ); add( math_box );
		add( sci_str );  add( sci_box );
		add( go );
		
		go.addActionListener( this ) ;
	}
	
	public void actionPerformed( ActionEvent e )
	{
		if(cnt >= max){
			//åxçê
		}
		else{
			names[cnt] = name_box.getText();
			
			String te, tj, tm, ts;
			te = eng_box.getText();
			tj = jap_box.getText();
			tm = math_box.getText();
			ts = sci_box.getText();
			
			eng_num[cnt] = Integer.parseInt( te );
			jap_num[cnt] = Integer.parseInt( tj );
			math_num[cnt] = Integer.parseInt( tm );
			sci_num[cnt] = Integer.parseInt( ts );
			
			if( 0<= eng_num[cnt]  && eng_num[cnt]  <= 100 &&
				0<= jap_num[cnt]  && jap_num[cnt]  <= 100 &&
				0<= math_num[cnt] && math_num[cnt] <= 100 &&
			    0<= sci_num[cnt]  && sci_num[cnt]  <= 100 ){
			    
			    cnt++;
			    paint = true;
			    repaint();
			}
			else{
				//åxçê
			}
		}
	}
	
	public void paint (Graphics g)
	{
		int x0 = 300;
		int y0 = 300;
		int sx = 600;
		int sy = 200;
		int val = 2;
		
		int i;
		//ÉOÉâÉtê¸
		g.setColor(Color.black);
		g.drawLine(x0-(100*val), y0, x0+(100*val), y0);
		g.drawLine(x0-(100*val), y0+1, x0+(100*val), y0+1);
		
		g.drawLine(x0, y0-(100*val), x0, y0+(100*val));
		g.drawLine(x0+1, y0-(100*val), x0+1, y0+(100*val));
		
		//ñ⁄ê∑ÇË
		for(i=0; i<5; i++){
			//yé≤
			int y = (y0-(100*val))+(i*50*val);
			g.drawLine(x0-5, y, x0+5, y);
			//xé≤
			int x = (x0-(100*val))+(i*50*val);
			g.drawLine(x, y0-5, x, y0+5);
			
			if(i == 0 || i==4){
				g.drawString("100", x0-25, y);
				g.drawString("100", x, y0-15);
			}
		}
		
		g.drawString("âpåÍ", x0+20, y0-(100*val)+2);
		g.drawString("çëåÍ", x0-(100*val)-25, y0);
		g.drawString("êîäw", x0+20, y0+(100*val)+2);
		g.drawString("óùâ»", x0+(100*val)+10, y0);
		
		//ï`âÊån
		if(paint){
			int poly_x[] = new int[4];
			int poly_y[] = new int[4];
			
			for(i=0; i<cnt; i++){
				poly_x[0] = x0;
				poly_y[0] = y0 - (eng_num[i]*val);
				
				poly_x[1] = x0 - (jap_num[i]*val);
				poly_y[1] = y0;
				
				poly_x[2] = x0;
				poly_y[2] = y0 + (math_num[i]*val);
				
				poly_x[3] = x0 + (sci_num[i]*val);
				poly_y[3] = y0;
				
				g.setColor(colors[i%7]);
				g.drawPolygon(poly_x, poly_y, 4);
				
				g.drawString("("+(i+1)+")   "+names[i], sx, sy+(i*10));
			}
			paint = false;
		}
	}
}