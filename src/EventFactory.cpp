// #include "EventFactory.h"

// #include "ClientArrival.h"
// #include "ElevatorArrival.h"
// #include <random>
// #include <vector>

// #include <iostream>
// #include <fstream>

// EventFactory::EventFactory(const std::shared_ptr<const Scenario> scenario)
//   : _scenario(scenario)
// {}

// EventFactory::~EventFactory()
// {}

// std::map<unsigned long, double> EventFactory::getProbabilities(const std::string seed,
//                                                                const unsigned long experiments,
//                                                                const double lambda) const
// {
//   std::seed_seq seed_sequence (seed.begin(), seed.end());
//   std::default_random_engine generator(seed_sequence);
//   std::poisson_distribution<int> distribution(lambda);

//   std::map<unsigned long, unsigned long> events;
//   for (int k = 0; k < experiments; ++k)
//   {
//     int event = distribution(generator);
//     ++events[event];
//   }

//   std::map<unsigned long, double> probabilities;
//   for (auto event : events)
//   {
//     probabilities[event.first] = 1.f * event.second / experiments;
//   }

//   return probabilities;
// }

// std::map<unsigned long, unsigned long> EventFactory::getClients(std::map<unsigned long, double> probabilities, const unsigned long population) const
// {
//   unsigned int available = population;

//   std::map<unsigned long, unsigned long> clientsPerEvent;
//   for (auto event : probabilities)
//   {
//     unsigned int amount = ceil(event.second * population);
//     if (amount > available) amount = available;
//     clientsPerEvent[event.first] = amount;
//     available -= amount;
//   }

//   return clientsPerEvent;
// }

// std::map<unsigned long, double> EventFactory::getDestProbabilities(const std::string seed,
//                                                                    const unsigned long experiments,
//                                                                    const int floors,
//                                                                    const int current_floor) const
// {
//   std::vector<float> probabilities(floors);
//   for (int i = 0; i < floors; i++)
//   {
//     probabilities[i] = i == current_floor ? 0 : 1;
//   }

//   std::default_random_engine generator;
//   std::discrete_distribution<int> distribution (probabilities.begin(), probabilities.end());

//   std::map<unsigned long, unsigned long> events;
//   for (int k = 0; k < experiments; ++k)
//   {
//     int event = distribution(generator);
//     ++events[event];
//   }

//   std::map<unsigned long, double> destProbabilities;
//   for (auto event : events)
//   {
//     destProbabilities[event.first] = 1.f * event.second / experiments;
//   }

//   return destProbabilities;
// }

// void EventFactory::initialize() const
// {
//   const std::string  seed               = _config->getString(Property::PoissonSeed);
//   const unsigned int totalSimulationTime = _config->getInt(Property::Duration);
//   const unsigned int timeBetweenEvents   = _config->getInt(Property::EventInterval);
//   const unsigned int experiments         = _config->getInt(Property::Experiments);

//   const float lambda = totalSimulationTime / timeBetweenEvents;
//   auto probabilities   = getProbabilities(seed, experiments, lambda);
//   // probabilities contém um map contendo na chave o evento (tempo) e no valor a probabilidade de um cliente chegar naquele evento

//   std::ofstream myfile;
//   myfile.open ("output.dat");

//   for (auto p : probabilities)
//   {
//     myfile << p.first << " " << p.second << "\n";
//   }

//   myfile.close();

//   //data = np.load(file); plt.normal(data); plt.show()

//   const unsigned int population = _config->getInt(Property::Population);
//   auto clientsPerEvent = getClients(probabilities, population);
//   // clientsPerEvent contém um map contendo na chave o evento (tempo) e no valor a quantidade absoluta de clientes que chegarão naquele instante

//   const unsigned int floors = _config->getInt(Property::Floors);
//   auto destinationProbabilities = getDestProbabilities(seed, experiments, floors, 0);
//   // destinationProbabilities contém um map cuja chave é o andar de destino e o valor é a probabilidade de um cliente ir para aquele andar

//   for (auto it : destinationProbabilities)
//   {
//     LOG(INFO) << "FLOOR: " << it.first << " :: " << it.second;
//   }

//   // agora tem que iterar sobre os clientes de cada evento do clientsPerEvent e destiná-los de acordo com as probabilidades de destinationProbabilities. isso fica para amanhã, pepepepepessoal! :)
// }
