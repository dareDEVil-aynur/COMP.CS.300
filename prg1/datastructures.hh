// Datastructures.hh
//
// Student name: Aynur Rahman Talukdar
// Student email: aynurrahman.talukdar@tuni.fi
// Student number: 150189473
// AI tool used and the version: ChatGPT, GPT 3.5
// The purpose of the use: optimizing time complexities
// The part(s) where it was utilized: get_affiliations_alphabetically, get_referenced_by_chain, get_all_references
// get_affiliations_closest_to, get_closest_common_parent, 

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <exception>

// Types for IDs
using AffiliationID = std::string;
using PublicationID = unsigned long long int;
using Name = std::string;
using Year = unsigned short int;
using Weight = int;
using Distance = int;

// Return values for cases where required thing was not found
AffiliationID const NO_AFFILIATION = "---";
PublicationID const NO_PUBLICATION = -1;
Name const NO_NAME = "!NO_NAME!";
Year const NO_YEAR = -1;
Weight const NO_WEIGHT = -1;

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};


// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Return value for cases where Distance is unknown
Distance const NO_DISTANCE = NO_VALUE;

// This exception class is there just so that the user interface can notify
// about operations which are not (yet) implemented
class NotImplemented : public std::exception
{
public:
    NotImplemented() : msg_{} {}
    explicit NotImplemented(std::string const& msg) : msg_{msg + " not implemented"} {}

    virtual const char* what() const noexcept override
    {
        return msg_.c_str();
    }
private:
    std::string msg_;
};

// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance: O(1)
    // Short rationale for estimate: Returns the size of the unordered_map
    unsigned int get_affiliation_count();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Clears the unordered_map which is O(n)
    void clear_all();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Iterating through all affiliations
    std::vector<AffiliationID> get_all_affiliations();

    // Estimate of performance: O(1)
    // Short rationale for estimate: Insertion in unordered_map
    bool add_affiliation(AffiliationID id, Name const& name, Coord xy);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Lookup in unordered_map
    Name get_affiliation_name(AffiliationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Lookup in unordered_map
    Coord get_affiliation_coord(AffiliationID id);


    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n * log(n))
    // Short rationale for estimate: Sorting a vector of n elements considering case-insensitive comparison. 
    std::vector<AffiliationID> get_affiliations_alphabetically();

    // Estimate of performance: O(n * log(n))
    // Short rationale for estimate: Sorting a vector of n elements based on distance
    std::vector<AffiliationID> get_affiliations_distance_increasing();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Linear search through all affiliations
    AffiliationID find_affiliation_with_coord(Coord xy);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Lookup and modification in an unordered_map
    bool change_affiliation_coord(AffiliationID id, Coord newcoord);


    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n)
    // Short rationale for estimate: Insertion in unordered_map
    bool add_publication(PublicationID id, Name const& name, Year year, const std::vector<AffiliationID>& affiliations);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Iterating through all publications
    std::vector<PublicationID> all_publications();

    // Estimate of performance: O(1)
    // Short rationale for estimate: Lookup in unordered_map
    Name get_publication_name(PublicationID id);

    // Estimate of performance: O(1)
    // Short rationale for estimate: Lookup in unordered_map
    Year get_publication_year(PublicationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Direct lookup in an unordered_map
    std::vector<AffiliationID> get_affiliations(PublicationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Lookups and modification in unordered_map
    bool add_reference(PublicationID id, PublicationID parentid);

    // Estimate of performance: O(n) 
    // Short rationale for estimate: Direct lookup in an unordered_map
    std::vector<PublicationID> get_direct_references(PublicationID id);

    // Estimate of performance: O(n) 
    // Short rationale for estimate: Lookups and modification in unordered_map
    bool add_affiliation_to_publication(AffiliationID affiliationid, PublicationID publicationid);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Iterating through all publications
    std::vector<PublicationID> get_publications(AffiliationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Iterating through all publications
    PublicationID get_parent(PublicationID id);

    // Estimate of performance: O(n * log(n))
    // Short rationale for estimate: Iterating and then sorting the results
    std::vector<std::pair<Year, PublicationID>> get_publications_after(AffiliationID affiliationid, Year year);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Iterative BFS traversal through the publications.
    std::vector<PublicationID> get_referenced_by_chain(PublicationID id);


    // Non-compulsory operations

    // Estimate of performance: O(n)
    // Short rationale for estimate: Iterative BFS traversal through the publications.
    std::vector<PublicationID> get_all_references(PublicationID id);

    // Estimate of performance: O(n * log(n))
    // Short rationale for estimate: Iterating through all affiliations and sorting based on distance.
    std::vector<AffiliationID> get_affiliations_closest_to(Coord xy);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Iterating through all publications to update affiliations.
    bool remove_affiliation(AffiliationID id);

    // Estimate of performance: O(n + m)
    // Short rationale for estimate: The function performs BFS to find all ancestors of two publications.
    PublicationID get_closest_common_parent(PublicationID id1, PublicationID id2);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Iterating through all publications to update references.
    bool remove_publication(PublicationID publicationid);


private:
    struct Affiliation
    {
        Name name;
        Coord coord;
    };

    struct Publication
    {
        Name name;
        Year year;
        std::vector<AffiliationID> affiliations;
        std::vector<PublicationID> references;
    };

    struct CaseInsensitiveCompare {
    bool operator()(const std::string& a, const std::string& b) const {
        return std::lexicographical_compare(
            a.begin(), a.end(),
            b.begin(), b.end(),
            [](char a, char b) { return std::tolower(a) < std::tolower(b); }
        );
    }
};

    std::unordered_map<Coord, AffiliationID> coordToAffiliation;
    std::unordered_map<AffiliationID, Affiliation> affiliations;
    std::unordered_map<PublicationID, Publication> publications;
};

#endif // DATASTRUCTURES_HH
