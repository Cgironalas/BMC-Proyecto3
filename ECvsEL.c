#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ECvsEL.h"

GtkWidget * windowInitial;
GtkWidget * entrySizew;
GtkWidget * entrySizev;
GtkWidget * entryW;
GtkWidget * entryV;
GtkWidget * spinnerMatch;
GtkWidget * spinnerMismatch;
GtkWidget * spinnerGap;

bool debug = true;

/**********************************/

void GenerateHileras(){
  printf("HERE\n");
  const char * base[4];
  base[0] = "A";
  base[1] = "C";
  base[2] = "G";
  base[3] = "T";

  v = malloc(sizeof(vSize + 1));
  w = malloc(sizeof(wSize + 1));

  strcpy(v,"");
  strcpy(w,"");

  for (int i = 0; i < vSize; i++){
    int position = rand() % 4;
    strcat(v, base[position]);
  }

  for (int i = 0; i < wSize; i++){
      int position = rand() % 4;
      strcat(w, base[position]);
  }
  if(!debug){
  gtk_entry_set_text(GTK_ENTRY(entryV), v);
  gtk_entry_set_text(GTK_ENTRY(entryW), w);}
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

    nwL();
  } else {
    GtkBuilder      *builder;

    gtk_init(NULL, NULL);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "GUI.glade", NULL);

    windowInitial = GTK_WIDGET(gtk_builder_get_object(builder, "window_initial"));
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

    gtk_widget_show(windowInitial);
    gtk_main();

    return 0;
  }
}

void startAlgorithm(){
  gap = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(spinnerGap));
  match = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(spinnerMatch));
  mismatch = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(spinnerMismatch));

  if (vSize > 0 && wSize > 0){
    printf("Continue\n");
  }
  ///CALL ALGORITHMS
}

void windowInitialDestroy(){
  gtk_main_quit();
}