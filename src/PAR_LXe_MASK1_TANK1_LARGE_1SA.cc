#include "PAR_LXe_MASK1_TANK1_LARGE_1SA.hh"
#include "G4ParticleGun.hh"
#include "G4Step.hh"
#include "G4UnitsTable.hh"


#include "G4SDManager.hh"
#include <numeric>
#include <vector>
#include "Randomize.hh"
#include <sys/time.h>
#include <time.h>
#include "G4SteppingManager.hh"
#include "G4ios.hh"

extern FILE *out_file;
extern double acum_Py;
extern double acum_Pz ;		
extern double event_count;
extern double y_TT;
extern double z_TT;
extern double GPM_Position;
extern double TT_Position;

PAR_LXe_MASK1_TANK1_LARGE_1SA::PAR_LXe_MASK1_TANK1_LARGE_1SA()			 
{;}

PAR_LXe_MASK1_TANK1_LARGE_1SA::~PAR_LXe_MASK1_TANK1_LARGE_1SA()
{;}

void PAR_LXe_MASK1_TANK1_LARGE_1SA::UserSteppingAction(const G4Step* aStep)
{
//  struct timeval hTimeValue;
//  gettimeofday(&hTimeValue, NULL);
//  CLHEP::HepRandom::setTheEngine(new CLHEP::DRand48Engine);
//  CLHEP::HepRandom::setTheSeed(hTimeValue.tv_usec);
  
  if(  aStep->GetTrack()->GetDefinition()->GetParticleName()                  == "opticalphoton" && 
       aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName() == "NeCH4_Window"  && 
       aStep->GetPostStepPoint()->GetTouchableHandle()->GetVolume()->GetName()== "expHall" ) {
   			G4double xP = aStep->GetPostStepPoint()->GetPosition().x();
    		G4double yP = aStep->GetPostStepPoint()->GetPosition().y();
    		G4double zP = aStep->GetPostStepPoint()->GetPosition().z();
//    G4double tt = aStep->GetPostStepPoint()->GetLocalTime();
//    G4cout << std::setprecision(3) 
//           << xP/mm << "  "
//           << yP/mm << "  " 
//           << zP/mm << "  "
//           << tt/ns << "  " << G4endl;
           
//           G4cout << "opticalphoton  opticalphoton  opticalphoton  opticalphoton"<< G4endl;
           
           if (xP == GPM_Position) {
           		G4double ran = G4UniformRand();
//           	G4cout << ran << G4endl;
           	if (ran <= 0.2) //quantum efficiency of PhotoCathode=0.2
           	{             
//              if (cou==0)
//              {
//              	m_y=yP/mm;
//              	m_z=zP/mm;
//              }
//              if (cou>0)
//               {
//               	m_y=(m_y*cou+yP/mm)/(cou+1);
//               	m_z=(m_z*cou+zP/mm)/(cou+1);
//               	}
//               cou=cou+1;
				acum_Py += yP;
 				acum_Pz += zP;	
 				event_count++ ;
              
//              G4cout <<  yP/mm << "  "<< zP/mm << G4endl;
           	}
           }
  }
  
       	
//      G4cout << aStep->GetTrack()->GetDefinition()->GetParticleName()<< G4endl;
//      G4cout << aStep->GetTrack()->GetTrackID()<< G4endl;
      
       if(  (aStep->GetTrack()->GetDefinition()->GetParticleName()=="neutron" ||
         aStep->GetTrack()->GetDefinition()->GetParticleName()=="gamma") && 
//         aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName()=="expHall" &&
//         aStep->GetPostStepPoint()->GetTouchableHandle()->GetVolume()->GetName()== "TT" )
           aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName()=="TT" && 
           aStep->GetPostStepPoint()->GetTouchableHandle()->GetVolume()->GetName()== "expHall")
         {  
           G4double x_TT = aStep->GetPostStepPoint()->GetPosition().x(); 
           if (x_TT==TT_Position)
           {
       	     y_TT = aStep->GetPostStepPoint()->GetPosition().y();
             z_TT = aStep->GetPostStepPoint()->GetPosition().z();
//             G4cout <<  y_TT << "  "<< z_TT << "  "<< x_TT<< G4endl;
           }
         }
         

//  if(aStep->GetTrack()->GetDefinition()->GetParticleName()=="opticalphoton" && 
//       aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName()=="NeCH4_Window" && 
//       aStep->GetPostStepPoint()->GetTouchableHandle()->GetVolume()->GetName()=="expHall" )
//       
//       
//  {
//    G4float xP = aStep->GetPostStepPoint()->GetPosition().x();
//    G4float yP = aStep->GetPostStepPoint()->GetPosition().y();
//    G4float zP = aStep->GetPostStepPoint()->GetPosition().z();
//    G4float tt = aStep->GetPostStepPoint()->GetLocalTime();
//fprintf(out_file,"%f  %f  %f  %f\n",xP/mm,yP/mm,zP/mm,tt/ns) ;
// /*   G4cout << std::setprecision(3) 
////           << " Pos X  ---- " << xP/mm << " mm "
////           << " Pos Y  ---- " << yP/mm << " mm " 
////           << " Pos Z  ---- " << zP/mm << " mm "
////           << " Time  ---- " << tt/ns << " ns " << G4endl;
//           << xP/mm << "  "
//           << yP/mm << "  " 
//           << zP/mm << "  "
//           << tt/ns << "  " << G4endl; */
//  }
 
}
