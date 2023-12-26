#include <a_star.h>
#include <maze.h>

using namespace std;
using namespace ecn;

// a node is a x-y position, we move from 1 each time
class Position : public Point
{
public:
    // constructor from coordinates
    Position(int _x, int _y, int _distance) : Point(_x, _y) {m_distance=_distance;}

    // constructor from base ecn::Point
    Position(ecn::Point _p) : Point(_p.x, _p.y) {}

    int distToParent()
    {
        // in cell-based motion, the distance to the parent is always 1
        return m_distance;
    }

    int isCorridor(int incrementX, int incrementY)
    {
        int count = 1;
        while(maze.isFree(this->x+incrementX*count, this->y+incrementY*count))
        {
            count++;
            int smallcount = 0;
            if (maze.isFree(this->x+incrementX*count+1, this->y+incrementY*count)) smallcount++;
            if (maze.isFree(this->x+incrementX*count-1, this->y+incrementY*count)) smallcount++;
            if (maze.isFree(this->x+incrementX*count, this->y+incrementY*count+1)) smallcount++;
            if (maze.isFree(this->x+incrementX*count, this->y+incrementY*count-1)) smallcount++;
        
            if (verbose > 3) cout << "\t\t\tnumber of neightbours " << smallcount << endl;  
            if (smallcount > 2) {
                count++;
                break;
            }  
        }
        if (verbose > 2) cout << "\t\tdistance to parent " << count-1 << endl;
        if (count>1) return count-1;
        return -1;
    }

    std::vector<Position> children()
    {
        // this method should return  all positions reachable from this one
        std::vector<Position> generated;

        // TODO add free reachable positions from this point
        //generated.reserve(4);
        if (verbose > 1) cout << "COORDINATES of parent "<< this->x << " " << this->y << endl;

        int dist = 0;
        if ((dist = isCorridor(1,0)) > 0) {
            generated.push_back(Position(this->x+dist, this->y, dist));
            if (verbose > 2) cout << "\tCOORDINATES of childern "<< this->x+dist << " " << this->y << endl;
        }
        if ((dist = isCorridor(-1,0)) > 0) {
            generated.push_back(Position(this->x-dist, this->y, dist));
            if (verbose > 2) cout << "\tCOORDINATES of childern "<< this->x-dist << " " << this->y << endl;
        }
        if ((dist = isCorridor(0,1)) > 0) {
            generated.push_back(Position(this->x, this->y+dist, dist));
            if (verbose > 2) cout << "\tCOORDINATES of childern "<< this->x << " " << this->y+dist << endl;
        }
        if ((dist = isCorridor(0,-1)) > 0) {
            generated.push_back(Position(this->x, this->y-dist, dist));
            if (verbose > 2) cout << "\tCOORDINATES of childern "<< this->x << " " << this->y-dist << endl;
        }
        if (verbose > 1) cout << "number of childern "<< generated.size() << endl;
        return generated;
    }
    int m_distance;
    static constexpr int verbose = 0;
};


int main( int argc, char **argv )
{
    // load file
    std::string filename = Maze::mazeFile("maze.png");
    if(argc == 2)
        filename = std::string(argv[1]);

    // let Point know about this maze
    Position::maze.load(filename);

    // initial and goal positions as Position's
    Position start = Position::maze.start(),
             goal = Position::maze.end();

    // call A* algorithm
    ecn::Astar(start, goal);

    // save final image
    Position::maze.saveSolution("cell");
    cv::waitKey(0);

}
