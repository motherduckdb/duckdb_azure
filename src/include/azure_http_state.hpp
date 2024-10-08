#pragma once

#include "duckdb/common/atomic.hpp"
#include "duckdb/common/file_opener.hpp"
#include "duckdb/common/file_system.hpp"
#include "duckdb/main/client_context_state.hpp"

namespace duckdb {

class AzureHTTPState : public ClientContextState {
public:
	AzureHTTPState() {
	}

public:
	//! Reset all counters
	void Reset();
	//! Helper functions to get the HTTP state
	static shared_ptr<AzureHTTPState> TryGetState(ClientContext &context);
	static shared_ptr<AzureHTTPState> TryGetState(optional_ptr<FileOpener> opener);

	bool IsEmpty() {
		return head_count == 0 && get_count == 0 && put_count == 0 && post_count == 0 && total_bytes_received == 0 &&
		       total_bytes_sent == 0;
	}

	atomic<idx_t> head_count {0};
	atomic<idx_t> get_count {0};
	atomic<idx_t> put_count {0};
	atomic<idx_t> post_count {0};
	atomic<idx_t> total_bytes_received {0};
	atomic<idx_t> total_bytes_sent {0};

	//! Called by the ClientContext when the current query ends
	void QueryEnd(ClientContext &context) override {
		Reset();
	}
	void WriteProfilingInformation(std::ostream &ss) override;
};

} // namespace duckdb
