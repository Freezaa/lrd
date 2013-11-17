//Uebung 2 LRD 
//deviate from mini_beispiel.cc 
//---------

#include "lrd_2.h"

void erodate_picture(){
	
	for (int v = 0; v <= start; v++){
		myoutpic.put(mypic.get());
	}
	for (int a = 0; a <= 1024; a++){
		for (int b = 0; b <= 1024; b++){
			erodate(a, b);
		}
	}
}

int erodate(int x, int y){
	
	bool elements[9];
	int schwelle_ero = 6;
	int m = 0;
	if (get_pixel_color(&a_pixel_color, x, y)){
		elements[0] = get_pixel_color(&a_pixel_color, x - 1, y - 1);
		elements[1] = get_pixel_color(&a_pixel_color, x, y - 1);
		elements[2] = get_pixel_color(&a_pixel_color, x + 1, y - 1);
		elements[3] = get_pixel_color(&a_pixel_color, x - 1, y);
		elements[4] = get_pixel_color(&a_pixel_color, x, y);
		elements[5] = get_pixel_color(&a_pixel_color, x + 1, y);
		elements[6] = get_pixel_color(&a_pixel_color, x - 1, y + 1);
		elements[7] = get_pixel_color(&a_pixel_color, x, y + 1);
		elements[8] = get_pixel_color(&a_pixel_color, x + 1, y + 1);

		for (int n = 0; n <= 8; n++){
			if (elements[n] == 1)
				m++;
		}

		if (m >= schwelle_ero){
			color_pixel_white();
		}
		else{
			color_pixel_black();
		}
	}
	else {
		color_pixel_black();	
	}
}

void color_pixel_black(){
	myoutpic.put(black);
	myoutpic.put(black);
	myoutpic.put(black);
}

void color_pixel_white(){
	myoutpic.put(white);
	myoutpic.put(white);
	myoutpic.put(white);
}

int get_pixel_color(struct pixel_color* pixel_rgb, int x, int y){
	
	mypic.open("ErdeOut.bmp");
	int offset = (y * 3) + (x * 1023 * 3);
	mypic.seekg(start+offset, ios::beg);
	pixel_rgb->b = mypic.get();
	pixel_rgb->g = mypic.get();
	pixel_rgb->r = mypic.get();
	//mypic.read(&pixel_rgb->b, 1);
	//mypic.read(&pixel_rgb->g, 1);
	//mypic.read(&pixel_rgb->r, 1);
	/*printf("%d", (short unsigned int)pixel_rgb->b);
	printf("%d", (short unsigned int)pixel_rgb->g);
	printf("%d \n", (short unsigned int)pixel_rgb->r); */
	mypic.close();
	if (pixel_rgb->b != 0 || pixel_rgb->g != 0 || pixel_rgb->r != 0){
		return 1;
	}
	else {
		return 0;
	}
}

int size(){
	mypic.open("Erde.bmp");
	for (int a = 0; a < 10; a++)
	{
		mypic.get();
	}
	start = mypic.get();	   			//Offset der Bilddaten in Byte vom Beginn der Datei an
	mypic.seekg(0, ios::end);   				//Suche Ende der Datei
	filesize = mypic.tellg();				//Dateigrˆﬂe
	mypic.close();
	return 0;
}

int filter(){

	myoutpic.open("ErdeOut.bmp");
	mypic.open("Erde.bmp");

	while (mypic.good())    				// Solange extrahierte Daten g¸ltig
	{
		cnt += 3;
		for (int i = 0; i <= 2; i++){
			rgb[i] = mypic.get();
		}
		//c = mypic.get();       				// lese Byte aus der Datei
		if (mypic.good())
			//printf("%d\n\r",(short unsigned int)c);		// Gebe Bytewert aus
		if ((cnt) > start&&(cnt) < filesize - 1)   		// Solange wir im Bildbereich sind
		{
			if ((short unsigned int)rgb[0] >= threshold[0] || (short unsigned int)rgb[1] >= threshold[1] || (short unsigned int)rgb[2] >= threshold[2])
			{
				myoutpic.put(white);
				myoutpic.put(white);
				myoutpic.put(white);
			}
			else{
				myoutpic.put(black);
				myoutpic.put(black);
				myoutpic.put(black);
			}
		}
		else
		{
			myoutpic.put(rgb[0]);
			myoutpic.put(rgb[1]);
			myoutpic.put(rgb[2]);
		}
	}
	mypic.close();           // schlieﬂe Datei
	myoutpic.close();
	return 0;
}

int filter_struct(){			

	myoutpic.open("ErdeOut.bmp");
	mypic.open("Erde.bmp");
	pixel_color* color;
	color = &a_pixel_color;

	pixel_color* tr_hold;
	tr_hold = &treshold_ref;
	tr_hold->r = 0x0F;
	tr_hold->g = 0x11;
	tr_hold->b = 0x11;

	while (mypic.good())    				// Solange extrahierte Daten g¸ltig
	{
		cnt += 3;
		color->r = mypic.get();
		color->g = mypic.get();
		color->b = mypic.get();
		//c = mypic.get();       				// lese Byte aus der Datei
		if (mypic.good())
			//printf("%d\n\r",(short unsigned int)c);		// Gebe Bytewert aus
		if ((cnt) > start&&(cnt) < filesize - 1)   		// Solange wir im Bildbereich sind
		{
			if ((short unsigned int)color->r >= tr_hold->r || (short unsigned int)color->g >= tr_hold->g || (short unsigned int)color->b >= tr_hold->b)
			{
				myoutpic.put(white);
				myoutpic.put(white);
				myoutpic.put(white);
			}
			else{
				myoutpic.put(black);
				myoutpic.put(black);
				myoutpic.put(black);
			}
		}
		else
		{
			myoutpic.put(color->r);
			myoutpic.put(color->g);
			myoutpic.put(color->b);
		}
	}

	mypic.close();           // schlieﬂe Datei
	myoutpic.close();
	return 0;
}

int main() {

	size();
	//filter();
	filter_struct();
	//get_pixel_color(&a_pixel_color, 500, 500);
	myoutpic.open("ErdeOutEro.bmp");
	mypic.open("ErdeOut.bmp");
	erodate_picture();
	mypic.close();
	myoutpic.close();
	return 0;
}