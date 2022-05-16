/* 

POLARIMETRO

*/ 


void polarimetro()
{

    // SCELTA INIZIALE 

    int starter = 5;
    char filename[100];

    cout << "\n\nANALISI DATI POLARIMETRO\n";

    do
    {
        cout << "Quale set di dati vuoi analizzare?\n";
        cout << "Angolo iniziale:   INSERISCI 0\nFruttosio:         INSERISCI 1\nSaccarosio:        INSERISCI 2\n";       
        cin >> starter;
        if (starter!=0 and starter !=1 and starter !=2) cout << "Hai inserito un valore non consentito.\n";
    } while (starter!=0 and starter !=1 and starter !=2);

    if (starter==0) sprintf(filename, "angolo_iniziale.txt");
    if (starter==1) sprintf(filename, "fruttosio.txt");
    if (starter==2) sprintf(filename, "saccarosio.txt");

    cout << "\nHai scelto di analizzare: " << filename << endl;





    // LETTURA DATI

    FILE *input = fopen(filename, "r" );

    if(!input)
    {
        cout << "Error: file could not be opened" << endl;
        exit(1);
    }

    // Conteggio 

    float temp_val;
    int   npoints = 0; 
    float min_val = 0;
    float max_val = 0;

    while(!feof(input))
    {
        fscanf(input,"%f\n",&temp_val);

        if(npoints == 0)
        {
        min_val = temp_val;
        max_val = temp_val;
        }
        else
        {
        if(temp_val < min_val)
            min_val = temp_val;

        if(temp_val > max_val)
            max_val = temp_val;
        }

        ++npoints;
    }

    cout << "\nSono state raccolte: " << npoints << " misure di angoli" << endl;
    cout << "min_val = " << min_val << " , max_val = " << max_val << endl << endl;

    // Lettura 

    rewind(input);
    float *theta = new float[npoints];

    int i=0;
    while(!feof(input))
    {
        fscanf(input,"%f\n",&temp_val);
        theta[i] = temp_val;
        ++i;
    }

    fclose(input);

    // Stampa dei valori
    
    int stampa = 5;

    do
    {
        cout << "Vuoi stampare i valori raccolti a schermo?\nSI:   INSERISCI 0\nNO:   INSERISCI 1\n";
        cin >> stampa;
        if (stampa!=0 and stampa!=1) cout << "Hai inserito un valore non consentito.\n";
    } while (stampa!=0 and stampa!=1);

    if (stampa==0)
    {
        cout << "\n{ ";
        for(int j=0;j<npoints-1;j++){
            cout << theta[j] << ", ";
        }
        cout << theta[npoints] << " }\n\n";
    }

    


    // ISTOGRAMMA 

    //int n_bins = (int)(npoints/5.0 + 0.5);
    int n_bins = (int)sqrt(npoints);
    float bin_size = (max_val - min_val) / n_bins;

    float min_hist_lim = min_val - bin_size;
    float max_hist_lim = max_val + bin_size; 
        
    TCanvas *canvas= new TCanvas("Istogramma", "Istogramma",800,600); 
    canvas->Clear();
    canvas->Divide(1);

    TH1F *isto_theta= new TH1F("Istogramma",filename,n_bins+1,min_hist_lim,max_hist_lim);

    for(int i=0 ; i < npoints ; i++)
    {
        isto_theta -> Fill(theta[i]);
    }


    // Abbellimenti 
    isto_theta->GetXaxis()->SetTitle("#theta"); // titolo dell'asse X
    isto_theta->GetYaxis()->SetTitle("Frequenze"); // titolo dell'asse Y
    //isto_theta->GetXaxis()->SetRangeUser(210,260);  //range lungo asse X
    //isto_theta->GetYaxis()->SetRangeUser(0,40); // range lungo asse Y

    //FIT CON GAUSSIANA
    TF1 *g = new TF1("g", "gaus",min_val,max_val);
    isto_theta->Fit("g","L");
    gStyle->SetOptFit(1);

    
    //DRAW
    isto_theta->Draw();


    

}