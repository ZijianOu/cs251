
#ifndef _GRID_WORLD_H
#define _GRID_WORLD_H

#include <vector>
#include <iostream>

using std::vector;


class GridWorld {

  private:
    // private stuff goes here!
    //   typedefs
    //   data members
    //   private helper functions
    //   etc.
	  
	  int p = 0;
	  int rows;
	  int cols;
	  int count;
	  int ID = 0;
	  struct Node {
		  Node *nextnode;
		  Node *prevnode;
		  int Node_id;
		  Node(Node *next, Node *prev, int id) {
			  nextnode = next;
			  prevnode = prev;
			  Node_id = id;

		  }

	  };
	
	 
	/*  struct List {
		  Node *front;
		  Node* *back;
	  };*/

	  struct District {
		  //int nrow;
		  //int ncol;
		  int ID;
		  Node *front = nullptr;
		  Node* back = nullptr;
		  int p = 0; //population
	  };

	  vector<vector<District>>districts;
	  
	  //District **grid;

	  struct People {
		  int nrow;
		  int ncol;
		  int ID;
		  bool alive;
		  Node *Nodeptr;
	  };

	  vector<People>Pep;

	  class dead {
		  Node *frontD = nullptr;
		  Node *backD = nullptr;
		  int p = 0;
		  int count;
		  int rows;
		  int cols;
	  public:
		  int pop_front(){
			  //using  .erase?
			  int tempID;
			  if (frontD==nullptr) {
				  return -1;
			  }
			  else {
				  Node *temp;
				  tempID = frontD->Node_id;
				  temp = frontD;
				  frontD->nextnode = frontD;
				  if (backD == frontD) {
					  backD = nullptr;
				  }
				  delete temp;
				   p--;
				   count = p;
			  }

		  }

		  void push_back(int id){
			  if (frontD == nullptr) {
				  Node* deadID = new Node(nullptr, nullptr, id);
				  frontD = deadID;
				  backD = deadID;
				  p++;
				  count = p;
			  }
			  else {
				  Node* deadID = new Node(nullptr, backD, id);
				  backD->nextnode = deadID;
				  backD = deadID;
				  p++;
				  count = p;
			  }

		  }
	  };
	  dead deadlist;
  public:
    /**
    * constructor:  initializes a "world" with nrows and
    *    ncols (nrows*ncols districtcs) in which all 
    *    districtricts are empty (a wasteland!).
    */
    GridWorld(unsigned nrows, unsigned ncols)   {
		rows = nrows;
		cols = ncols;
		districts.resize(nrows);
			for (int i = 0; i < districts.size(); i++) {
				districts[i].resize(ncols);
			}

      // your constructor code here!
    }
    ~GridWorld(){
      // your destructor code here.
    }

    /*
     * function: birth
     * description:  if row/col is valid, a new person is created
     *   with an ID according to rules in handout.  New person is
     *   placed in district (row, col)
     *
     * return:  indicates success/failure
     */
	bool birth(int row, int col, int &id) {
		while ( row <0 ||row>rows|| col <0||col>cols) {
			return false;
		}
		int tempID;
		tempID = deadlist.pop_front();
		if (tempID == -1) {
			tempID = ID;
			ID++;
			People newperson;
			newperson.nrow = row;
			newperson.ncol = col;
			newperson.ID = tempID;
			newperson.alive = true;
			Pep.push_back(newperson);
		}
		else {
			Pep[ID].nrow = row;
			Pep[ID].ncol = col;
			Pep[ID].ID = id;
			Pep[ID].alive = true;
		}
		Node *newnode = new Node(districts[row][col].back, nullptr, id);
		districts[row][col].back = newnode;
		if (newnode->prevnode != nullptr) {
			newnode->prevnode->nextnode = newnode;
		}
		p++;
		districts[row][col].p++;
		id = tempID;
		return true;
		//count = p;
		
		//else {
		//	id = p + 1;
		//	People human;
		//	human.ID = id;
		//	human.alive = true;
		//	districts.at(tempID).row = row;
		//	
		//}
		//p++;
		//if(frontD!= nullptr) {
		//	tempID = frontD->Node_id;
		//	Pep.at(tempID).Nodeptr = frontD;
		//	Pep.at(tempID).nrow = row;
		//	Pep.at(tempID).ncol = col;
		//	Pep.at(tempID).alive = true;
		//	push_back(tempID);
		//	//People human;
		//	//id = p + 1;
		//	//human.ID = id;
		//	//human.alive = true;
		//	//districts.row = row;
		//	//districts.col = col;
		//	frontD = frontD->nextnode;
		//	id = tempID;
		//	return true;
		//}
		/*else {
			ID = ID + 1;

		}*/
	}
		/*
		 * function: death
		 * description:  if given person is alive, person is killed and
		 *   data structures updated to reflect this change.
		 *
		 * return:  indicates success/failure
		 */
		bool death(int personID) {
			if (Pep.size() <= personID) {
				return false;
			}
			if (Pep[personID].alive == false) {
				return false;
			}
			deadlist.push_back(personID);
			Pep[personID].alive = false;
			if (Pep[personID].Nodeptr->prevnode != nullptr) {
				Pep[personID].Nodeptr->prevnode->nextnode = Pep[personID].Nodeptr->nextnode;
			}
			if (Pep[personID].Nodeptr->nextnode != nullptr) {
				Pep[personID].Nodeptr->nextnode->prevnode = Pep[personID].Nodeptr->prevnode;
			}
			delete Pep[personID].Nodeptr;
			districts[Pep[personID].nrow][Pep[personID].ncol].p--;
			p--;
			//delete districts[Pep[personID].nrow][Pep[personID].ncol];
			//delete districts[rows][cols].personID;
			//delete Pep[personID].col;
			
			return true;
		}

		/*
		 * function: whereis
		 * description:  if given person is alive, his/her current residence
		 *   is reported via reference parameters row and col.
		 *
		 * return:  indicates success/failure
		 */
		bool whereis(int id, int &row, int &col)const {
			if (Pep.size() <= id) {
				return false;
			}
			if (Pep[id].alive == false) {
				return false;
			}
			row = Pep[id].nrow;
			col = Pep[id].ncol;
			return true;
		}

		/*
		 * function: move
		 * description:  if given person is alive, and specified target-row
		 *   and column are valid, person is moved to specified district and
		 *   data structures updated accordingly.
		 *
		 * return:  indicates success/failure
		 *
		 * comment/note:  the specified person becomes the 'newest' member
		 *   of target district (least seniority) --  see requirements of members().
		 */
		bool move(int id, int targetRow, int targetCol) {
			if (Pep.size() <= id) {
				return false;
			}
			if (Pep[id].alive == false) {
				return false;
			}
			if (targetRow <0 || targetRow>rows || targetCol <0 || targetCol>cols) {
				return false;
			}
			districts[Pep[id].nrow][Pep[id].ncol].p--;
			if (Pep[id].Nodeptr->prevnode != nullptr) {
				Pep[id].Nodeptr->prevnode->nextnode = Pep[id].Nodeptr->nextnode;
			}
			if (Pep[id].Nodeptr->nextnode != nullptr) {
				Pep[id].Nodeptr->nextnode->prevnode = Pep[id].Nodeptr->prevnode;
			}
			//Node *newnode = new Node(districts[row][col].back, nullptr, id);
			
			Pep[id].Nodeptr->prevnode = districts[targetRow][targetCol].back;
			Pep[id].Nodeptr->nextnode = nullptr;
			districts[targetRow][targetCol].back = Pep[id].Nodeptr;
			if (Pep[id].Nodeptr->prevnode != nullptr) {
				Pep[id].Nodeptr->prevnode->nextnode = Pep[id].Nodeptr;
			}
			//delete Pep[id].Nodeptr;
			//districts[targetRow][targetCol] = districts[Pep[id].nrow][Pep[id].ncol];
			Pep[id].nrow = targetRow;
			Pep[id].ncol = targetCol;
			//districts[Pep[id].nrow][Pep[id].ncol].delete;
			districts[targetRow][targetCol].p++;
			//gird[districts[id].row][districts[id].col].delete(districts[id].Nodeptr);
			return true;
		}

		std::vector<int> * members(int row, int col)const {
			//vector<int>*memb = new vector<int>;
			vector<int>*district = new vector<int>;
			vector<int>*emptyvec = new vector<int>;			//Node *p = front;
			//while (p != nullptr) {
			//	memb->push_back(p->Node_id);
			//	p = p->nextnode;
			//}
			while (row <0 || row>rows || col <0 || col>cols) {
				return emptyvec;
			}
			//district=
			return district;
		}

		/*
		 * function: population
		 * description:  returns the current (living) population of the world.
		 */
		int population()const {
			return p;
		}

		/*
		 * function: population(int,int)
		 * description:  returns the current (living) population of specified
		 *   district.  If district does not exist, zero is returned
		 */
		int population(int row, int col)const {

			if  (row <0 || row>rows || col <0 || col>cols) {
				return false;
			}
			else{
				int Pop = districts[row][col].p;
			}
			return districts[row][col].p;
			//return 0;
		}

		/*
		 * function: num_rows
		 * description:  returns number of rows in world
		 */
		int num_rows()const {
			return rows;
		}
	
		/*
		 * function: num_cols
		 * description:  returns number of columns in world
		 */
		int num_cols()const {
			return cols;
		}

	};



#endif
