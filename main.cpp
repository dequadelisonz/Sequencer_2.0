#include <iostream>
#include "KnotCycle.h"

//#include <malloc.h>

using std::cout;
using std::endl;

int main()
{

    KnotCycle kCycle("cycle.json",50000);

    kCycle.start();

    // // cout << "Beginning : " << endl;
    // // malloc_stats();

    // JSONdoc jsonDoc("cycle.json", 50000);
    
    // //std::cout << "indirizzo jsondoc in main :" << &jsonDoc << std::endl;

    // Sequencer seq(jsonDoc);

    // if (seq.hasRead())
    // {

    //     cout << "read ok" << endl;
    //     // while (true)
    //     // {

    //     // }
    // };

    // // Sequencer seqencer;

    // char desc [] = "prova";
    // char instr [] = "7_ON";

    // //Pass p(1, desc, 0.1, instr);
    // Pass p(1, "passo 1", 0.1, "7_ON");

    // Pass q(2,"passo 2",0.2,"8_OFF");

    // cout << "Report passi singoli" << endl;
    // cout << p.getId () << endl;
    // cout << p.getDescription() << endl;
    // cout << p.getDuration() << endl;
    // uP_instruction_t uPI = p.get_uP_instruction();
    // cout << uPI.pin << endl;
    // cout << uPI.status << endl;
    // cout << endl;
    // cout << q.getId () << endl;
    // cout << q.getDescription() << endl;
    // cout << q.getDuration() << endl;
    // uPI = q.get_uP_instruction();
    // cout << uPI.pin << endl;
    // cout << uPI.status << endl;
    // cout << endl;

    // cout << "Report passi listati" << endl;

    // PassesList pl(0.0,0.2);

    // pl.push (p);
    // pl.push (q);

    // //auto it = pl.begin ();

    // for (auto it = pl.getBegin ();
    //     it != pl.getEnd ();
    //     ++it)
    // {

    //     cout << it -> getId () << endl;
    //     cout << it -> getDescription() << endl;
    //     cout << it -> getDuration() << endl;
    //     uP_instruction_t uPI = it -> get_uP_instruction();
    //     cout << uPI.pin << endl;
    //     cout << uPI.status << endl;
    //     cout << endl;
    // }

    // cout << "Esecuzione terminata" << endl;

    return 0;
}
