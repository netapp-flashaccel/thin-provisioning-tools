#ifndef PERSISTENT_DATA_DATA_STRUCTURES_BLOOM_FILTER_H
#define PERSISTENT_DATA_DATA_STRUCTURES_BLOOM_FILTER_H

#include "persistent-data/transaction_manager.h"
#include "persistent-data/data-structures/bitset.h"

#include <boost/shared_ptr.hpp>

//----------------------------------------------------------------

namespace persistent_data {
	class bloom_filter {
	public:
		typedef boost::shared_ptr<bloom_filter> ptr;
		typedef typename persistent_data::transaction_manager::ptr tm_ptr;

		// nr_bits must be a power of two
		bloom_filter(tm_ptr tm,
			     unsigned nr_bits, unsigned nr_probes);

		bloom_filter(tm_ptr tm, block_address root,
			     unsigned nr_bits_power, unsigned nr_probes);

		block_address get_root() const;

		bool test(uint64_t b); // not const due to caching effects in bitset
		void set(uint64_t b);
		void flush();

		void print_debug(ostream &out);

	private:
		void print_residency(ostream &out);

		void fill_probes(block_address b, vector<unsigned> &probes) const;

		tm_ptr tm_;
		unsigned nr_bits_;
		persistent_data::bitset bits_;
		unsigned nr_probes_;
		uint64_t mask_;
	};
}

//----------------------------------------------------------------

#endif
