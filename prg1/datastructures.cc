// Datastructures.cc
//
// Student name: Aynur Rahman Talukdar
// Student email: aynurrahman.talukdar@tuni.fi
// Student number: 150189473

#include "datastructures.hh"

#include <random>

#include <cmath>

#include <algorithm>

#include <unordered_set> 

#include <queue>  

#include <stack>

#include <map>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{
    // Write any initialization you need here
}

Datastructures::~Datastructures()
{
    // Write any cleanup you need here
}

unsigned int Datastructures::get_affiliation_count()
{
    return affiliations.size();
}

void Datastructures::clear_all()
{
    affiliations.clear();
    publications.clear();
}

std::vector<AffiliationID> Datastructures::get_all_affiliations()
{
    std::vector<AffiliationID> affiliation_ids;
    affiliation_ids.reserve(affiliations.size());

    for (const auto& affiliation : affiliations)
    {
        affiliation_ids.push_back(affiliation.first);
    }

    return affiliation_ids;
}

bool Datastructures::add_affiliation(AffiliationID id, const Name& name, Coord xy)
{
    if (affiliations.find(id) != affiliations.end())
    {
        return false;
    }
    affiliations[id] = {name, xy};
    return true;
}

Name Datastructures::get_affiliation_name(AffiliationID id)
{
    auto it = affiliations.find(id);
    if (it != affiliations.end())
    {
        return it->second.name;
    }
    return NO_NAME;
}

Coord Datastructures::get_affiliation_coord(AffiliationID id)
{
    auto it = affiliations.find(id);
    if (it != affiliations.end())
    {
        return it->second.coord;
    }
    return NO_COORD;
}

std::vector<AffiliationID> Datastructures::get_affiliations_alphabetically()
{
    std::vector<std::pair<std::string, AffiliationID>> sortedAffiliations;
    
    std::transform(affiliations.begin(), affiliations.end(), std::back_inserter(sortedAffiliations),
        [](const auto& aff) { return std::make_pair(aff.second.name, aff.first); });

    std::sort(sortedAffiliations.begin(), sortedAffiliations.end(),
        [](const auto& a, const auto& b) { return a.first < b.first; });

    std::vector<AffiliationID> sortedIds;
    sortedIds.reserve(sortedAffiliations.size());

    std::transform(sortedAffiliations.begin(), sortedAffiliations.end(), std::back_inserter(sortedIds),
        [](const auto& entry) { return entry.second; });

    return sortedIds;
}

std::vector<AffiliationID> Datastructures::get_affiliations_distance_increasing()
{
    std::vector<AffiliationID> ids;
    ids.reserve(affiliations.size());

    std::transform(affiliations.begin(), affiliations.end(), std::back_inserter(ids),
        [](const auto& aff) { return aff.first; });

    std::sort(ids.begin(), ids.end(), [this](const AffiliationID& a, const AffiliationID& b) {
        auto dist_a = std::pow(affiliations[a].coord.x, 2) + std::pow(affiliations[a].coord.y, 2);
        auto dist_b = std::pow(affiliations[b].coord.x, 2) + std::pow(affiliations[b].coord.y, 2);
        return dist_a < dist_b;
    });

    return ids;
}

AffiliationID Datastructures::find_affiliation_with_coord(Coord xy)
{
    auto it = coordToAffiliation.find(xy);
    if (it != coordToAffiliation.end()) {
        return it->second;
    } else {
        return NO_AFFILIATION;
    }
}

bool Datastructures::change_affiliation_coord(AffiliationID id, Coord newcoord)
{
    auto it = affiliations.find(id);
    if (it != affiliations.end())
    {
        it->second.coord = newcoord;
        return true;
    }
    return false;
}

bool Datastructures::add_publication(PublicationID id, const Name& name, Year year, const std::vector<AffiliationID>& affiliations)
{
    if (publications.find(id) != publications.end())
    {
        return false;
    }

    publications[id] = {name, year, affiliations, {}};
    return true;
}

std::vector<PublicationID> Datastructures::all_publications()
{
    std::vector<PublicationID> ids;
    for (const auto& pub : publications)
    {
        ids.push_back(pub.first);
    }
    return ids;
}

Name Datastructures::get_publication_name(PublicationID id)
{
    auto it = publications.find(id);
    if (it != publications.end())
    {
        return it->second.name;
    }
    return NO_NAME;
}

Year Datastructures::get_publication_year(PublicationID id)
{
    auto it = publications.find(id);
    if (it != publications.end())
    {
        return it->second.year;
    }
    return NO_YEAR;
}

std::vector<AffiliationID> Datastructures::get_affiliations(PublicationID id)
{
    auto it = publications.find(id);
    if (it != publications.end())
    {
        return it->second.affiliations;
    }
    return {NO_AFFILIATION};
}

bool Datastructures::add_reference(PublicationID id, PublicationID parentid)
{
    if (publications.find(id) != publications.end() && publications.find(parentid) != publications.end())
    {
        publications[parentid].references.push_back(id);
        return true;
    }
    return false;
}

std::vector<PublicationID> Datastructures::get_direct_references(PublicationID id)
{
    auto it = publications.find(id);
    if (it != publications.end())
    {
        return it->second.references;
    }
    return {NO_PUBLICATION};
}

bool Datastructures::add_affiliation_to_publication(AffiliationID affiliationid, PublicationID publicationid)
{
    if (affiliations.find(affiliationid) != affiliations.end() &&
        publications.find(publicationid) != publications.end())
    {
        publications[publicationid].affiliations.push_back(affiliationid);
        return true;
    }
    return false;
}

std::vector<PublicationID> Datastructures::get_publications(AffiliationID id)
{
    std::vector<PublicationID> publication_ids;
    for (const auto& publication : publications)
    {
        if (std::find(publication.second.affiliations.begin(), publication.second.affiliations.end(), id) != publication.second.affiliations.end())
        {
            publication_ids.push_back(publication.first);
        }
    }
    return publication_ids;
}

PublicationID Datastructures::get_parent(PublicationID id)
{
    for (const auto& publication : publications)
    {
        if (std::find(publication.second.references.begin(), 
                      publication.second.references.end(), id) != publication.second.references.end())
        {
            return publication.first;
        }
    }
    return NO_PUBLICATION;
}

std::vector<std::pair<Year, PublicationID>> Datastructures::get_publications_after(AffiliationID affiliationid, Year year)
{
    std::multimap<Year, PublicationID> sortedPublications;

    for (const auto& publication : publications)
    {
        if (publication.second.year >= year &&
            std::find(publication.second.affiliations.begin(), 
                      publication.second.affiliations.end(), affiliationid) != publication.second.affiliations.end())
        {
            sortedPublications.emplace(publication.second.year, publication.first);
        }
    }

    std::vector<std::pair<Year, PublicationID>> result;
    result.reserve(sortedPublications.size());

    for (const auto& entry : sortedPublications)
    {
        result.push_back(entry);
    }

    return result;
}

std::vector<PublicationID> Datastructures::get_referenced_by_chain(PublicationID id)
{
    if (publications.find(id) == publications.end())
    {
        return {NO_PUBLICATION};
    }

    std::unordered_set<PublicationID> visited;
    std::vector<PublicationID> result;
    result.reserve(publications.size());

    std::queue<PublicationID> to_visit;
    to_visit.push(id);

    while (!to_visit.empty())
    {
        PublicationID current_id = to_visit.front();
        to_visit.pop();

        for (const auto& pub : publications)
        {
            if (visited.find(pub.first) == visited.end() &&
                std::find(pub.second.references.begin(), pub.second.references.end(), current_id) != pub.second.references.end())
            {
                visited.insert(pub.first);
                result.push_back(pub.first);
                to_visit.push(pub.first);
            }
        }
    }

    if (result.size() == 1 && result[0] == id)
    {
        return {};
    }

    return result;
}

std::vector<PublicationID> Datastructures::get_all_references(PublicationID id)
{
    std::vector<PublicationID> result;
    std::unordered_set<PublicationID> visited;
    std::stack<PublicationID> to_visit;

    to_visit.push(id);
    while (!to_visit.empty())
    {
        PublicationID current_id = to_visit.top();
        to_visit.pop();

        if (visited.find(current_id) != visited.end()) {
            continue;
        }

        visited.insert(current_id);

        for (const auto& ref_id : publications[current_id].references)
        {
            if (visited.find(ref_id) == visited.end())
            {
                to_visit.push(ref_id);
                result.push_back(ref_id);
            }
        }
    }

    return result;
}


std::vector<AffiliationID> Datastructures::get_affiliations_closest_to(Coord xy)
{
    std::vector<std::pair<Distance, AffiliationID>> dist_affiliations;
    for (const auto& aff : affiliations)
    {
        Distance dist = std::sqrt(std::pow(aff.second.coord.x - xy.x, 2) + std::pow(aff.second.coord.y - xy.y, 2));
        dist_affiliations.push_back({dist, aff.first});
    }
    std::sort(dist_affiliations.begin(), dist_affiliations.end());
    
    std::vector<AffiliationID> closest_affiliations;
    for (size_t i = 0; i < std::min<size_t>(3, dist_affiliations.size()); ++i)
    {
        closest_affiliations.push_back(dist_affiliations[i].second);
    }
    return closest_affiliations;
}

bool Datastructures::remove_affiliation(AffiliationID id)
{
    if (affiliations.find(id) == affiliations.end())
    {
        return false;
    }
    for (auto& pub : publications)
    {
        pub.second.affiliations.erase(std::remove(pub.second.affiliations.begin(), pub.second.affiliations.end(), id), pub.second.affiliations.end());
    }
    affiliations.erase(id);
    return true;
}

PublicationID Datastructures::get_closest_common_parent(PublicationID id1, PublicationID id2)
{
    auto ancestors_of = [this](PublicationID id) -> std::unordered_set<PublicationID> {
        std::unordered_set<PublicationID> ancestors;
        std::queue<PublicationID> queue;
        queue.push(id);

        while (!queue.empty())
        {
            PublicationID current = queue.front();
            queue.pop();

            for (const auto& ref_id : publications)
            {
                if (std::find(ref_id.second.references.begin(), ref_id.second.references.end(), current) != ref_id.second.references.end())
                {
                    if (ancestors.find(ref_id.first) == ancestors.end())
                    {
                        ancestors.insert(ref_id.first);
                        queue.push(ref_id.first);
                    }
                }
            }
        }
        return ancestors;
    };

    std::unordered_set<PublicationID> ancestors1 = ancestors_of(id1);
    std::unordered_set<PublicationID> ancestors2 = ancestors_of(id2);

    for (const auto& ancestor : ancestors1)
    {
        if (ancestors2.find(ancestor) != ancestors2.end())
        {
            return ancestor;
        }
    }

    return NO_PUBLICATION;
}

bool Datastructures::remove_publication(PublicationID publicationid)
{
    if (publications.find(publicationid) == publications.end())
    {
        return false;
    }
    for (auto& pub : publications)
    {
        pub.second.references.erase(std::remove(pub.second.references.begin(), pub.second.references.end(), publicationid), pub.second.references.end());
    }
    publications.erase(publicationid);
    return true;
}


