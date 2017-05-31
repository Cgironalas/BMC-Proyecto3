#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "ECvsEL.h"

GtkWidget * windowInitial;
GtkWidget * windowResult;
GtkWidget * entrySizew;
GtkWidget * entrySizev;
GtkWidget * entryW;
GtkWidget * entryV;
GtkWidget * spinnerMatch;
GtkWidget * spinnerMismatch;
GtkWidget * spinnerGap;

GtkWidget * entrySpaceC;
GtkWidget * entryTimeC;
GtkWidget * entryScoringC;


GtkWidget * entrySpaceL;
GtkWidget * entryTimeL;
GtkWidget * entryScoringL;


GtkWidget *g_tableGeo;
GtkWidget ***tableGeoData;
GtkWidget *g_scrolledwindow_finalTableGeno;


double segundosL;
double segundosC;

bool debug =false;

/**********************************/

void GenerateHileras(){
  printf("HERE\n");
  const char * base[4];
  base[0] = "A";
  base[1] = "C";
  base[2] = "G";
  base[3] = "T";

  v = (char*)calloc(vSize,sizeof(char)); ;
  w = (char*)calloc(wSize,sizeof(char)); ;

  for (int i = 0; i < vSize; i++){
    int position = rand() % 4;
    strcat(v, base[position]);
  }

  for (int i = 0; i < wSize; i++){
      int position = rand() % 4;
      strcat(w, base[position]);
  }

  if(!debug){
    //printV();
    //printW();

    gtk_entry_set_text(GTK_ENTRY(entryV), v);
    gtk_entry_set_text(GTK_ENTRY(entryW), w);
  }

}

void getLength(){
  char v[gtk_entry_get_text_length (GTK_ENTRY(entrySizev)) + 1];
  strcpy(v, gtk_entry_get_text(GTK_ENTRY(entrySizev)));
  char w[gtk_entry_get_text_length (GTK_ENTRY(entrySizew)) + 1];
  strcpy(w, gtk_entry_get_text(GTK_ENTRY(entrySizew)));

  vSize = atoi(v);
  wSize = atoi(w);

  if (wSize <= 0 || vSize <=0){
    printf("ERROR\n");
  }
  else{
    GenerateHileras();
  }
}


int main(int argc, char const *argv[]) {
  if(debug) {
    vSize = 10;
    wSize = 10;
    GenerateHileras();
    printV();
    printW();
    //printLList(BestScorePre(0, vSize, 0, wSize));

    //printf("\n\n");

    //GenerateHileras();
    //printV();
    //printW();
    //printLList(BestScorePos(vSize, 0, wSize, 0));

  //  nwL();
  } else {
    GtkBuilder      *builder;

    gtk_init(NULL, NULL);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "GUI.glade", NULL);

    windowInitial = GTK_WIDGET(gtk_builder_get_object(builder, "window_initial"));
    gtk_builder_connect_signals(builder, NULL);

    windowResult = GTK_WIDGET(gtk_builder_get_object(builder, "window_result"));
    gtk_builder_connect_signals(builder, NULL);

    entrySizew = GTK_WIDGET(gtk_builder_get_object(builder, "entry_sizeW"));
    entrySizev = GTK_WIDGET(gtk_builder_get_object(builder, "entry_sizeV"));

    entryW = GTK_WIDGET(gtk_builder_get_object(builder, "entryW"));
    entryV = GTK_WIDGET(gtk_builder_get_object(builder, "entryV"));

    spinnerMatch = GTK_WIDGET(gtk_builder_get_object(builder, "spinMatch"));
    gtk_spin_button_set_range (GTK_SPIN_BUTTON(  spinnerMatch), -10000, 10000);
    gtk_spin_button_set_increments (GTK_SPIN_BUTTON(  spinnerMatch), 1, 3);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON( spinnerMatch), 1);

    spinnerGap = GTK_WIDGET(gtk_builder_get_object(builder, "spinGap"));
    gtk_spin_button_set_range (GTK_SPIN_BUTTON(spinnerGap), -10000, 10000);
    gtk_spin_button_set_increments (GTK_SPIN_BUTTON(spinnerGap), 1, 3);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON( spinnerGap), -2);

    spinnerMismatch = GTK_WIDGET(gtk_builder_get_object(builder, "spinMis"));
    gtk_spin_button_set_range (GTK_SPIN_BUTTON(spinnerMismatch), -10000, 10000);
    gtk_spin_button_set_increments (GTK_SPIN_BUTTON(spinnerMismatch), 1, 3);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON( spinnerMismatch), -1);


    entryTimeL = GTK_WIDGET(gtk_builder_get_object(builder, "entryTimeL"));
    entryScoringL = GTK_WIDGET(gtk_builder_get_object(builder, "entryScoringL"));
    entrySpaceL =GTK_WIDGET(gtk_builder_get_object(builder, "entrySpaceL"));

    entryTimeC = GTK_WIDGET(gtk_builder_get_object(builder, "entryTimeC"));
    entryScoringC = GTK_WIDGET(gtk_builder_get_object(builder, "entryScoringC"));
    entrySpaceC =GTK_WIDGET(gtk_builder_get_object(builder, "entrySpaceC"));

    g_scrolledwindow_finalTableGeno= GTK_WIDGET(gtk_builder_get_object(builder,"scrolledwindow_finalTableGeno"));



    gtk_widget_show(windowInitial);
    gtk_main();

    return 0;
  }
}

void setnwC(){
  char * str = malloc(sizeof(int));
  char * timeC = malloc(sizeof(double));
  sprintf(str, "%d", maxScoringC);
  sprintf(timeC,"%f",segundosC);
  gtk_entry_set_text(GTK_ENTRY(entryScoringC),str);
  gtk_entry_set_text(GTK_ENTRY(entryTimeC),timeC);
  int size = strlen(vC);


    tableGeoData = calloc(2,sizeof(GtkWidget**));

    g_tableGeo = gtk_grid_new ();
    gtk_container_add (GTK_CONTAINER (g_scrolledwindow_finalTableGeno), g_tableGeo);

    for(int j = 0; j < 2; j++) {
      tableGeoData[j] = calloc(size,sizeof(GtkWidget*));
    }

    for(int row =0; row < 2; row++)
    {
      for(int column=0; column < size; column++)
    {
      tableGeoData[row][column] = gtk_entry_new();
    gtk_entry_set_width_chars(GTK_ENTRY(tableGeoData[row][column]),2);
    gtk_widget_set_sensitive(tableGeoData[row][column],FALSE);
    gtk_grid_attach (GTK_GRID (g_tableGeo),tableGeoData[row][column] , column, row, 1, 1);
    char letter[1];
    if (row ==0){
        strncpy(letter,&vC[column],1);
    }
    else{
      strncpy(letter,&wC[column],1);

    }

    gtk_entry_set_text (GTK_ENTRY(tableGeoData[row][column]),letter);

  }
  }
}
void startAlgorithm(){
  gap = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(spinnerGap));
  match = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(spinnerMatch));
  mismatch = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(spinnerMismatch));

  if (vSize > 0 && wSize > 0){
    printf("Continue\n");


    clock_t tiempo_inicio, tiempo_final;


    tiempo_inicio = clock();
    nwC();


    tiempo_final = clock();

    segundosC = (double)(tiempo_final-tiempo_inicio) / CLOCKS_PER_SEC; /*según que estes midiendo el tiempo en segundos es demasiado grande*/



    setnwC();
     gtk_widget_show_all(windowResult);
      //gtk_widget_destroy(windowInitial);
    gtk_widget_hide(windowInitial);
  }

}

void windowInitialDestroy(){
  gtk_main_quit();
}
