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

#include <unordered_map>

#include <queue>

#include <stack>

#include <map>

#include <functional>

#include <set>

#include <limits>

#include <vector>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end - start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range - 1)(rand_engine);

    return static_cast<Type>(start + num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{
    struct CoordHash
    {
        std::size_t operator()(const Coord &coord) const
        {
            return std::hash<int>()(coord.x) ^ std::hash<int>()(coord.y);
        }
    };
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

    for (const auto &affiliation : affiliations)
    {
        affiliation_ids.push_back(affiliation.first);
    }

    return affiliation_ids;
}

bool Datastructures::add_affiliation(AffiliationID id, const Name &name, Coord xy)
{
    if (affiliations.find(id) != affiliations.end())
    {
        return false;
    }
    affiliations[id] = {name, xy, {}};
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
                   [](const auto &aff)
                   { return std::make_pair(aff.second.name, aff.first); });

    std::sort(sortedAffiliations.begin(), sortedAffiliations.end(),
              [](const auto &a, const auto &b)
              { return a.first < b.first; });

    std::vector<AffiliationID> sortedIds;
    sortedIds.reserve(sortedAffiliations.size());

    std::transform(sortedAffiliations.begin(), sortedAffiliations.end(), std::back_inserter(sortedIds),
                   [](const auto &entry)
                   { return entry.second; });

    return sortedIds;
}

std::vector<AffiliationID> Datastructures::get_affiliations_distance_increasing()
{
    std::vector<AffiliationID> ids;
    ids.reserve(affiliations.size());

    std::transform(affiliations.begin(), affiliations.end(), std::back_inserter(ids),
                   [](const auto &aff)
                   { return aff.first; });

    std::sort(ids.begin(), ids.end(), [this](const AffiliationID &a, const AffiliationID &b)
              {
        auto dist_a = std::pow(affiliations[a].coord.x, 2) + std::pow(affiliations[a].coord.y, 2);
        auto dist_b = std::pow(affiliations[b].coord.x, 2) + std::pow(affiliations[b].coord.y, 2);
        return dist_a < dist_b; });

    return ids;
}

AffiliationID Datastructures::find_affiliation_with_coord(Coord xy)
{
    auto it = coordToAffiliation.find(xy);
    if (it != coordToAffiliation.end())
    {
        return it->second;
    }
    else
    {
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

bool Datastructures::add_publication(PublicationID id, const Name &name, Year year, const std::vector<AffiliationID> &affiliations)
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
    for (const auto &pub : publications)
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
    for (const auto &publication : publications)
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
    for (const auto &publication : publications)
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

    for (const auto &publication : publications)
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

    for (const auto &entry : sortedPublications)
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

        for (const auto &pub : publications)
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

        if (visited.find(current_id) != visited.end())
        {
            continue;
        }

        visited.insert(current_id);

        for (const auto &ref_id : publications[current_id].references)
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
    for (const auto &aff : affiliations)
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
    for (auto &pub : publications)
    {
        pub.second.affiliations.erase(std::remove(pub.second.affiliations.begin(), pub.second.affiliations.end(), id), pub.second.affiliations.end());
    }
    affiliations.erase(id);
    return true;
}

PublicationID Datastructures::get_closest_common_parent(PublicationID id1, PublicationID id2)
{
    auto ancestors_of = [this](PublicationID id) -> std::unordered_set<PublicationID>
    {
        std::unordered_set<PublicationID> ancestors;
        std::queue<PublicationID> queue;
        queue.push(id);

        while (!queue.empty())
        {
            PublicationID current = queue.front();
            queue.pop();

            for (const auto &ref_id : publications)
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

    for (const auto &ancestor : ancestors1)
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
    for (auto &pub : publications)
    {
        pub.second.references.erase(std::remove(pub.second.references.begin(), pub.second.references.end(), publicationid), pub.second.references.end());
    }
    publications.erase(publicationid);
    return true;
}

std::vector<Connection> Datastructures::get_connected_affiliations(AffiliationID id)
{
    std::vector<Connection> result;

    auto affiliation_iter = affiliations.find(id);
    if (affiliation_iter == affiliations.end())
    {
        return result;
    }

    for (const auto &pub_pair : publications)
    {
        const auto &pub = pub_pair.second;

        if (std::find(pub.affiliations.begin(), pub.affiliations.end(), id) != pub.affiliations.end())
        {
            for (const auto &aff_id : pub.affiliations)
            {
                if (aff_id != id)
                {
                    auto it = std::find_if(result.begin(), result.end(), [&aff_id](const Connection &conn)
                                           { return conn.aff2 == aff_id; });

                    if (it != result.end())
                    {
                        it->weight++;
                    }
                    else
                    {
                        result.emplace_back(Connection{id, aff_id, 1});
                    }
                }
            }
        }
    }

    return result;
}

std::vector<Connection> Datastructures::get_all_connections()
{
    std::vector<Connection> result;
    std::map<std::pair<AffiliationID, AffiliationID>, int> connections_map;

    for (const auto &publication_pair : publications)
    {
        const auto &affiliations_list = publication_pair.second.affiliations;

        for (size_t i = 0; i < affiliations_list.size(); ++i)
        {
            for (size_t j = i + 1; j < affiliations_list.size(); ++j)
            {
                AffiliationID aff1 = std::min(affiliations_list[i], affiliations_list[j]);
                AffiliationID aff2 = std::max(affiliations_list[i], affiliations_list[j]);

                connections_map[{aff1, aff2}]++;
            }
        }
    }

    for (const auto &connection : connections_map)
    {
        result.push_back(Connection{connection.first.first, connection.first.second, connection.second});
    }

    return result;
}

Path Datastructures::get_any_path(AffiliationID source, AffiliationID target)
{
    if (affiliations.find(source) == affiliations.end() || affiliations.find(target) == affiliations.end())
    {
        return {};
    }

    std::queue<AffiliationID> to_visit;
    std::unordered_map<AffiliationID, AffiliationID> predecessors;
    std::unordered_set<AffiliationID> visited;
    to_visit.push(source);
    visited.insert(source);

    while (!to_visit.empty())
    {
        AffiliationID current = to_visit.front();
        to_visit.pop();

        if (current == target)
        {
            Path path;
            AffiliationID at = target;
            while (at != source)
            {
                AffiliationID pred = predecessors[at];
                int weight = 0;
                for (const auto &pub_pair : publications)
                {
                    const auto &pub_affiliations = pub_pair.second.affiliations;
                    if (std::find(pub_affiliations.begin(), pub_affiliations.end(), pred) != pub_affiliations.end() &&
                        std::find(pub_affiliations.begin(), pub_affiliations.end(), at) != pub_affiliations.end())
                    {
                        weight++;
                    }
                }
                path.insert(path.begin(), Connection{pred, at, weight});
                at = pred;
            }
            return path;
        }

        for (const auto &publication_pair : publications)
        {
            const auto &pub_affiliations = publication_pair.second.affiliations;
            if (std::find(pub_affiliations.begin(), pub_affiliations.end(), current) != pub_affiliations.end())
            {
                for (const auto &adj_affiliation : pub_affiliations)
                {
                    if (visited.find(adj_affiliation) == visited.end())
                    {
                        visited.insert(adj_affiliation);
                        predecessors[adj_affiliation] = current;
                        to_visit.push(adj_affiliation);
                    }
                }
            }
        }
    }

    return {};
}

Path Datastructures::get_path_with_least_affiliations(AffiliationID source, AffiliationID target)
{
    if (affiliations.find(source) == affiliations.end() || affiliations.find(target) == affiliations.end())
    {
        return {};
    }
    auto compare = [](const std::pair<AffiliationID, int> &a, const std::pair<AffiliationID, int> &b)
    {
        return a.second > b.second;
    };
    std::priority_queue<std::pair<AffiliationID, int>, std::vector<std::pair<AffiliationID, int>>, decltype(compare)> pq(compare);

    std::unordered_map<AffiliationID, AffiliationID> previous; // To store the previous node in the optimal path
    std::unordered_map<AffiliationID, int> weights;            // To store the weights of the paths to each node
    std::unordered_set<AffiliationID> visited;                 // To keep track of visited nodes

    for (const auto &aff : affiliations)
    {
        weights[aff.first] = std::numeric_limits<int>::max();
    }
    weights[source] = 0;

    pq.push({source, 0});

    while (!pq.empty())
    {
        auto [current, current_weight] = pq.top();
        pq.pop();

        if (current_weight > weights[current])
        {
            continue;
        }

        if (current == target)
        {
            break;
        }

        for (const auto &connection : get_connected_affiliations(current))
        {
            AffiliationID neighbor = connection.aff2;
            int weight_through_current = current_weight + connection.weight;

            if (weight_through_current < weights[neighbor])
            {
                weights[neighbor] = weight_through_current;
                previous[neighbor] = current;
                pq.push({neighbor, weight_through_current});
            }
        }
    }

    if (weights[target] == std::numeric_limits<int>::max())
    {
        return {};
    }

    Path path;
    for (AffiliationID at = target; at != source; at = previous[at])
    {
        int edge_weight = 1;
        for (const auto &connection : get_connected_affiliations(previous[at]))
        {
            if (connection.aff2 == at)
            {
                edge_weight = connection.weight;
                break;
            }
        }
        path.insert(path.begin(), {previous[at], at, edge_weight});
    }

    return path;
}

Path Datastructures::get_path_of_least_friction(AffiliationID /*source*/, AffiliationID /*target*/)
{
    // Replace the line below with your implementation
    throw NotImplemented("get_path_of_least_friction()");
}

Distance Datastructures::calculate_distance(AffiliationID aff1, AffiliationID aff2)
{
    Coord coord1 = affiliations[aff1].coord;
    Coord coord2 = affiliations[aff2].coord;
    return static_cast<Distance>(std::hypot(coord2.x - coord1.x, coord2.y - coord1.y));
}

PathWithDist Datastructures::get_shortest_path(AffiliationID source, AffiliationID target)
{
    if (affiliations.find(source) == affiliations.end() || affiliations.find(target) == affiliations.end())
    {
        return {};
    }

    std::priority_queue<std::pair<AffiliationID, Distance>,
                        std::vector<std::pair<AffiliationID, Distance>>,
                        std::greater<std::pair<AffiliationID, Distance>>>
        pq;

    std::unordered_map<AffiliationID, Distance> dist;
    std::unordered_map<AffiliationID, AffiliationID> prev;

    for (const auto &aff : affiliations)
    {
        dist[aff.first] = std::numeric_limits<Distance>::max();
    }
    dist[source] = 0;

    pq.push({source, 0});

    while (!pq.empty())
    {
        AffiliationID current = pq.top().first;
        pq.pop();

        for (const auto &conn : get_connected_affiliations(current))
        {
            AffiliationID neighbor = conn.aff2;
            Distance new_dist = dist[current] + calculate_distance(current, neighbor);

            if (new_dist < dist[neighbor])
            {
                dist[neighbor] = new_dist;
                prev[neighbor] = current;
                pq.push({neighbor, new_dist});
            }
        }
    }

    if (dist[target] == std::numeric_limits<Distance>::max())
    {
        return {};
    }

    PathWithDist path_with_dist;

    for (AffiliationID at = target; at != source; at = prev[at])
    {
        AffiliationID from = prev[at];
        Distance distance = calculate_distance(from, at);
        path_with_dist.push_back({{from, at, 1}, distance});
    }

    std::reverse(path_with_dist.begin(), path_with_dist.end());

    for (auto &[conn, dist] : path_with_dist)
    {
        for (const auto &connection : get_connected_affiliations(conn.aff1))
        {
            if (connection.aff2 == conn.aff2)
            {
                conn.weight = connection.weight;
                break;
            }
        }
    }

    return path_with_dist;
}
