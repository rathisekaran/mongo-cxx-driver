// Copyright 2014 MongoDB Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "catch.hpp"
#include "helpers.hpp"

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/types/value.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/result/insert_one.hpp>

TEST_CASE("insert_one", "[insert_one][result]") {
    using namespace bsoncxx;

    mongocxx::instance::current();

    builder::stream::document build;
    auto oid = types::b_oid{bsoncxx::oid{bsoncxx::oid::init_tag}};
    build << "_id" << oid << "x" << 1;

    mongocxx::result::bulk_write b(document::value(build.view()));

    mongocxx::result::insert_one insert_one(std::move(b), types::value{oid});

    SECTION("returns correct response") {
        REQUIRE(insert_one.inserted_id() == oid);
    }
}
